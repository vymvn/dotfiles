# HTB - OpenSourse


## Enumration 
#### Basic scan 

```bash
nmap -sC -sV -Pn 10.10.11.164
```
Port 80 and port 22 are open

Seems to be running a Python Flask cloud file sharing app

Clicking upload without a file causes an error which reveals some information

Using burpsuite, sending a request with `../../../etc/passwd` as file name ( Doesnt work because file name is sanitized ) returns a response which contains:
SECRET "Cul7YdEvFOEEyixHXNjc"

Ok so after research I discovered that it is using Werkzeug which is a web dubugging tool that devopers use to debug the website. 
A feature of this the debugger is the interactive console which can be accessed by navigating to `domain.com/console`.

But in our case the console window is pin code protected. Running the application in devolpment mode locally using the dockerfile we can see how the pin code can be used.
The code that generates the pin code is open source and can be viewed.

TODO: Figure out how to generate the same code on the running website

