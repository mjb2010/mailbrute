mailbrute
=========

This is a fork of mailbrute.c, a program that launches a "RCPT TO:"-based dictionary attack on an SMTP server in an attempt to enumerate usernames.

The original mailbrute.c was written in 1999 by axess <axess@mail.com> of the old b0f (buffer0verflow) security research group. Since 2000 it has lived at <http://packetstormsecurity.com/files/author/231/>, and since 2003 a copy has also lived at <http://examples.oreilly.com/networksa/tools/> because it was referenced by the O'Reilly book "Network Security Assessment".

Changes:

  2013-09-22: [mjb2010] Only print the "Recipient ok" response, not the whole 500-char receive buffer.
