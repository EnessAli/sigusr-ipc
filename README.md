# SIGUSR IPC

A minimal inter-process communication (IPC) system built entirely on UNIX signals (`SIGUSR1` and `SIGUSR2`), encoding arbitrary strings as binary bitstreams transmitted between processes.

## Protocol

Each character is transmitted as 8 bits, MSB first:

```
Sender encodes A (0x41 = 01000001):
  bit 7: 0 → SIGUSR1
  bit 6: 1 → SIGUSR2
  bit 5: 0 → SIGUSR1
  bit 4: 0 → SIGUSR1
  bit 3: 0 → SIGUSR1
  bit 2: 0 → SIGUSR1
  bit 1: 0 → SIGUSR1
  bit 0: 1 → SIGUSR2
```

The receiver reconstructs the character by accumulating bits in a static variable and emitting the character when 8 bits have been received. A null terminator signals end of transmission.

## Acknowledgment (Bonus)

The server sends `SIGUSR1` back to the client after each bit, and the client waits for acknowledgment before sending the next — ensuring zero bit loss on any POSIX-compliant system.

## Build & Run

```bash
make

# Terminal 1 — start server (prints its PID)
./server
# Server PID: 12345

# Terminal 2 — send message
./client 12345 "Hello, World!"
```

## Tech Stack

`C` `UNIX Signals` `SIGUSR1/2` `sigaction` `kill()` `IPC` `Bit Manipulation`

