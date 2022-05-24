# Basic Working Of File Transfer using UDP Socket

1. The server starts and waits for filename.
2. The client sends a filename.
3. The server receives filename.
   If file is present,server starts reading file and continues to send buffer filled with file contents encrypted until file end is reached.
4. End is marked by EOF.
5. File is received as buffer until EOF is received, Then it is decrypted
6. If the file is not present, then file not found is sent to the Server.
