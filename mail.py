import smtplib
import sys

if len(sys.argv) < 4:
    print("Usage: python mail.py <recipient_email> <subject> <body>")
    sys.exit(1)

recipient = sys.argv[1]
subject = sys.argv[2]
body = sys.argv[3].replace("\\n", "\n")

body = body.encode("utf-8").decode("utf-8")

# Sender email credentials
sender_email = "kritikamodi766@gmail.com"
password = "XXX"  # Use an App Password, NOT your normal password

message = f"""From: {sender_email}
To: {recipient}
Subject: {subject}
MIME-Version: 1.0
Content-Type: text/plain; charset="utf-8"
Content-Transfer-Encoding: 8bit

Dear {recipient},

Here is your electricity bill:

{body}

Please make the payment before the due date to avoid late charges.

Best Regards,  
Electricity Board
"""

try:
    with smtplib.SMTP("smtp.gmail.com", 587) as server:
        server.starttls()
        server.login(sender_email, password)
        server.sendmail(sender_email, recipient, message.encode("utf-8"))  # Proper encoding

    print(f"✅ Email sent successfully to {recipient}!")
except Exception as e:
    print(f"❌ Error sending email: {e}")
