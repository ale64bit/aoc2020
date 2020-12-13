use std::io::*;

fn wait(t: u32, k: u32) -> u32 {
    k - t % k
}

fn main() -> Result<()> {
    let mut input = String::new();
    stdin().lock().read_to_string(&mut input)?;
    let mut lines = input.lines();
    let t: u32 = lines.next().unwrap().parse().unwrap();
    let id = lines.next().unwrap().split(',').fold(t - 1, |acc, s| {
        if s == "x" {
            acc
        } else {
            let id: u32 = s.parse().unwrap();
            if wait(t, id) < wait(t, acc) {
                id
            } else {
                acc
            }
        }
    });

    Ok(println!("{}", id * wait(t, id)))
}
