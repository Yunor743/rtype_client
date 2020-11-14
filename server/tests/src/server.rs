use std::net::UdpSocket;
use std::net::Ipv4Addr;

#[derive(Debug)]
pub struct Server {
    pub ip: Ipv4Addr,
    pub port: u16,
    pub socket: UdpSocket,
}

impl Server {
    pub fn new(ip: Ipv4Addr, port: u16) -> Self {
        let socket = UdpSocket::bind((ip.clone(), 24556)).expect("coudln't bind to address");
        socket.connect((ip.clone(), port)).unwrap();
        Server {
            ip,
            port,
            socket,
        }
    }
    pub fn send(&self, data: &Vec<u8>) {
        self.socket.send(data).unwrap();
    }
    pub fn recv(&self, size: usize) -> Vec<u8> {
        let mut data = Vec::with_capacity(size);
        self.socket.recv_from(&mut data).unwrap();
        data
    }
}
