# 42sh
An Epitech shell project  
The 42sh is a End year project at Epitech    

## The project
The goal of this project is to code a shell as complete as possible
Its a big Epitech project, which last 1 month and a half.
The behaviour of our shell is between Bash and Tcsh

## The team
For this project we were 5 : arthur.knoepflin@epitech.eu, benjamin.solca@epitech.eu, ludovic.leuzzi@epitech.eu, maxime.jenny@epitech.eu and nicolas.polomack@epitech.eu
* Benjamin build the ll parser
* Ludovic build some internal function and made the unit test
* Maxime build the auto-completation engine
* Nicolas build the main execution engine
* And me, I build the external system like DualCast or ConfigurationOnTheAir

## The shell
### The builtins
* `alias`: Alias command permit you to set an alias for a command  
At the difference with Bash, the alias are saved, when you relaunch the shell, they are restored  
Example: `alias ll ls -l`: Now, when you enter `ll` in the command prompt, you will get the result of `ls -l`       
If you enter just `alias`, you will get the list of alias, and if you enter `alias *an_aliased_command*` you will get the command wich the alias is associated  

* `builtins`: Give you the list of the existing alias

* `cd`: Change the current directory

* `config`: Permit you to launch the configuration on the air (See Configuration of the air section)

* `dualcast`: Permit you to launch DualCast (See DualCast section)

* `echo`: Display string, variable or environment variable

* `env`: Permit you to list environment variables, but you can also launch a program with a specific environment set
  * Flags:
    * `-u $val` or `--unset=$val`: Destruct temporarly an environment variable named by $val
    * `-i` or `--ignore-environment`: Destruct temporarly all environment variable
    * `-0` or `--null`: Display you the list of environment variable without '\n' (You can't launch a program with this flag)

Example: `env` list you the environment variables  
`env -i ls` launch ls command without any environment variables  
`env -u PATH bash` launch bash without PATH variable

* `exit`: Exit the current shell

* `history`: Show you the 500 last command entered

* `parser_ll`: Its a builtins that we have set up for explain the operation of a ll parser  
When you execute this builtins, you will enter an command input (like `ls test.c || echo "Failed" > result`) and the system show you the tree of the ll parsing

* `prompt`: Permit you to quickly change the prompt

* `set`: Set a variable  
Example: `set test` create a variable, named test, with no value  
`set test=value` create a variable, named test, wich contains 'value'

* `setenv`: Set a environment variable, work like `set`

* `unalias`: Destruct an alias  
Example: `unalias ll` destruct the alias named 'll'

* `unset`: Destruct a variable  
Example: `unset test` destruct the variable named 'test'

* `unsetenv`: Destruct an environment variable, work like `unset`

* `where`: Show the emplacement of a command

* `which`: Show you the emplacement of a command and alias

### Configuration on the air
For simplify the configuration and the personalisation of the shell, we have set up an online configuration tool.

For starting it, just execute the builtins `config`, the terminal shall prompt 'Server started' and a new page should be open on your navigator.
If its not, make sure you have `google-chrome` or `firefox`.

On the first tab you can manage the environment variable  
You can delete, update or add environment variable

On the second tab you can manage the prompt

On the third tab you can see the information in real time of your pc  
You can see:
* The name of the distribution you use
* The name of the machine
* The platform you execute
* The version of the OS
* The name of the processor
* And the usage of the RAM

On the last tab you can use an integrate terminal for execute litle and finite command (like ls or cat)

You can stop the configuration by clicking on the cross

### DualCast
DualCast is an exclusive technology wich is between SSH and TeamViewer

The concept is to connect to terminal, the first terminal will be a duplicate of the second terminal.  
DualCast can be useful in help case. 

For example, if you face a problem and you ask a person for help you. Admit that you provide him SSH access, when this person help you, you can't see how he fix the problem because SSH is opaque. With DualCast you can provide a temporarly access to your serve and you can see every command he enter.

For starting a new DualCast session, just enter `dualcast start`. The system will provide you a token compose by 4 numbers.

For connecting to a DualCast session, enter `dualcast connect $ip_address` where $ip_address is the ip of the computer you want to connect, after that, if the ip address is correct and if the person have enter `dualcast start`, the system will ask you the session token, you have to enter the token that you friend gave you.

For security reason, if a person try to connect to your DualCast server and enter a bad token, a message will be prompt on the DualCast server
          
During the connection, on the server side you can stop by pressing 'Enter', on the client side, you can stop by pressing 'Ctrl-C'.



