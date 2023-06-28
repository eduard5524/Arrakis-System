# Arrakis-System

Arrakis System, a system that tries restore minimal connectivity to the planet in a post-pandemic, post-apocalyptic and dystopia situation.
Mainly, the system will have three programs, the Atreides server, the Fremen terminals and the
Harkonen attacking programs. Below, you can see the functional diagram of the system.</br></br>

Next, we go on to explain in a little more detail the general operation of the system.</br>
• Atreides server; It has a passive behavior, it monitors and displays the actions on the screen
#that occur It is a socket server, which interacts with Fremen client sockets through
of the specified communication protocol. The configuration data is extracted from a file. Likewise,
it saves information related to user management in main and secondary memory.</br>
• Fremen Terminals; The user interacts with them through a shell and connects with a connection from
sockets with the server through the specified communication protocol. The configuration data
extract from a file. Likewise, it also allows you to run Linux commands.</br>
• Harkonen attackers; This program connects to the Atreides server and performs two actions; scan
the PIDs and delete one at random and, delete the files with the extension “.jpg” from the Fremen folder.</br>
