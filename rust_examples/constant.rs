// An attempt to reproduce the dangerous behavior of the corresponding constant.c

struct Example {
    x: i32,
    y: i32,
    z: i32,
}

// Function signature reinforces explicit read-only assurance.
fn black_box(c: Box<&&Example>) {
    // Cast to mutable? to try and coerce drop
    drop(*(&mut(*c)));
}

fn main() {
    // Explicitly create a read-only boxed constant value.
    let mut a: Example = Example { x: 1, y: 2, z: 3 };
    let mut b: Box<&Example> = Box::new(&mut a);
    let c: Box<&&Example> = Box::new(&mut b);


    // Pass refererence to read-only value to 'trust_me'.
    black_box(c);

    b.x = 4;
    b.y = 5;
    b.z = 6;
}