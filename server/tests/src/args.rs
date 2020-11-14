use std::error::Error;

pub struct Args {
    pub port: u16,
}

impl Args {
    pub fn from_env() -> Result<Self, Box<dyn Error>> {
        let arg: Vec<String> = std::env::args().collect();
        assert_eq!(arg.len(), 2);
        Ok(Args {
            port: arg[1].parse::<u16>()?,
        })
    }
}
