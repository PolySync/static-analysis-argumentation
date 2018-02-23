// An attempt to reproduce the dangerous behavior of the corresponding pattern.c

struct Example {
    x: i32,
    y: i32,
    z: i32,
}

// Enumeration intended for use.
enum Action {
    ApplyBrake = 1,
    ApplyThrottle = 2,
}

// Enumeration that can results dangerous behavior.
enum Destruct {
    SelfDestruct = 1,
    DoNotSelfDestruct = 2,
}

fn black_box( pattern: i32 ) {
    match pattern {
        Destruct::SelfDestruct => panic!("Memory corrupted."),
        Destruct::DoNotSelfDestruct => {},
    }
}

fn main() {
    let pattern = Action::ApplyThrottle;
    black_box(pattern);
}
