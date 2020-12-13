use std::io::*;

fn euclid(m: i128, n: i128) -> (i128, i128) {
    let (mut a, mut b) = (0, 1);
    let (mut aa, mut bb) = (1, 0);
    let (mut c, mut d) = (m, n);

    while c % d != 0 {
        let (q, r) = (c / d, c % d);
        c = d;
        d = r;
        {
            let t = aa;
            aa = a;
            a = t - q * a;
        }
        {
            let t = bb;
            bb = b;
            b = t - q * b;
        }
    }
    assert_eq!(d, 1);
    (a, b)
}

fn main() -> Result<()> {
    let mut input = String::new();
    stdin().lock().read_to_string(&mut input)?;
    let (ans, _) = input
        .lines()
        .skip(1)
        .next()
        .unwrap()
        .split(',')
        .enumerate()
        .map(|(i, s)| s.parse::<i128>().map(|n| (i, n)))
        .flatten()
        .fold((0, 1), |(a, r), (i, s)| {
            let (m, n) = euclid(r, s);
            let mut x = a * n * s + (s - (i as i128)) * m * r;
            if x < 0 {
                x = r * s - -x % (r * s);
            }
            (x % (r * s), r * s)
        });
    Ok(println!("{}", ans))
}
