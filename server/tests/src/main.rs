use std::net::Ipv4Addr;
use std::rc::Rc;
use std::error::Error;

const INPUT_PATH: &str = "./input/";
const OUTPUT_PATH: &str = "./output/";

mod server;
use server::Server;

mod args;
use args::Args;

fn main() -> Result<(), Box<dyn Error>> {
    let args = Args::from_env()?;
    let serv = Rc::new(Server::new(Ipv4Addr::LOCALHOST, args.port));
    let mut vec = Vec::new();
    for n in std::fs::read_dir(INPUT_PATH).unwrap() {
        if let Ok(n) = n {
            let n = n.path();
            if n.is_file() {
                vec.push(Tests::new(Rc::clone(&serv), n.file_name().unwrap().to_str().unwrap()));
            }
        }
    }
    for mut i in vec {
        i.run();
        println!("{}", i);
    }
    Ok(())
}

#[derive(Debug)]
pub struct Tests {
    server: Rc<Server>,
    path: String,
    pub input: Vec<u8>,
    pub output: Vec<u8>,
    pub result: Option<bool>,
}

impl Tests {
    pub fn new(server: Rc<Server>, filename: &str) -> Self {
        let input = std::fs::read(String::from(INPUT_PATH) + filename).unwrap();
        let output = std::fs::read(String::from(OUTPUT_PATH) + filename).unwrap();
        Tests { server, path: String::from(filename), input, output, result: None }
    }

    pub fn run(&mut self) {
        self.server.send(&self.input);
        let ret = self.server.recv(self.output.len());
        self.result.replace(ret == self.output);
    }
}

impl std::fmt::Display for Tests {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self.result {
            Some(true) => write!(f, "{}... [OK]", self.path),
            Some(false) => write!(f, "{}... [KO]", self.path),
            None => write!(f, "{}... [NOT_TESTED]", self.path),
        }
    }
}

