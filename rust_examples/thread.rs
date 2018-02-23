// An attempt to reproduce the dangerous behavior of the corresponding thread.c

use std::{thread, time};

struct Example {
    x: i32,
    y: i32,
    z: i32,
}

// Modifies counter resource!
fn black_box( b: Box<&mut Example>) {
    while b.x < 10 {

        thread::sleep(time::Duration::from_secs(0));

        if b.x >= 10 {
            panic!("Memory corrupted.");
        }

        b.x = b.x + 1;
    }
}

fn main() {
    // Declare / set up thread resources.
    let thread_count = 5;
    let mut handles: Vec<Option<thread::JoinHandle<()>>> = vec![];

    let a: Example = Example { x: 1, y: 2, z: 3 };
    let b: Box<&mut Example> = Box::new(&mut a);

    // Spawn threads.
    for _ in 0..thread_count {
        handles.push(Some(thread::spawn( || { black_box(b)})));
    }

    // Allow threads to finish work.
    for ref mut handle in &mut handles {
        if let Some(h) = handle.take() {
            h.join().unwrap();
        }
    }
}
