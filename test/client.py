import socket

HOST = "localhost"
PORT = 6379

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect((HOST, PORT))

commands = ["SET name Anunay", "GET name", "DEL name", "GET name"]
for cmd in commands:
    client.sendall(cmd.encode() + b"\n")
    response = client.recv(1024)
    print(f"Response: {response.decode().strip()}")

client.close()
