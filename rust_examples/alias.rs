// An attempt to reproduce the dangerous behavior of the corresponding alias.c

struct Example {
    x: i32,
    y: i32,
    z: i32,
}

fn black_box( _: &Box<&&Example> ) {
    panic!("Memory corrupted.");
}

fn main() {
    // Assign an arbitrary value to a variable for aliasing.
    let mut a: Example = Example { x: 1, y: 2, z: 3 };
    let mut b: Box<&Example> = Box::new(&mut a);
    let c: Box<&&Example> = Box::new(&mut b);

    black_box(&c);

    b.x = 4;
    b.y = 5;
    b.z = 6;
}
