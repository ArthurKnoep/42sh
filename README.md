# 42sh
An Epitech shell project.  
The 42sh is an end-year project at Epitech.    

## The project
The goal of this project is to code a shell as complete as possible.  
Its a big Epitech project, which lasts 1 month and a half.  
The behaviour of our shell is between Bash and Tcsh.

## The team
For this project we were 5 : arthur.knoepflin@epitech.eu, benjamin.solca@epitech.eu, ludovic.leuzzi@epitech.eu, maxime.jenny@epitech.eu and nicolas.polomack@epitech.eu
* Benjamin built the ll parser
* Ludovic built some internal function and made the unit test
* Maxime built the auto-completion engine
* Nicolas built the main execution engine
* And me, I built the external system like DualCast or ConfigurationOnTheAir

## The shell
### The builtins
* `alias`: Permits you to set an alias for a command  
At the difference with Bash, the aliases are saved, when you relaunch the shell, they are restored  
Example:  
  - `alias` Shows you the list of aliases
  - `alias ll` Shows you the command aliased by `ll`  
  - `alias ll ls -l`: Defines `ll` to alias `ls -l`. Then, when you enter `ll` in the command prompt, you will get the result of `ls -l`  

* `builtins`: Gives you the list of the existing builtins

* `cd`: Changes the current directory

* `config`: Permits you to launch the configuration on the air (See ConfigurationOnTheAir section)

* `dualcast`: Permits you to launch DualCast (See DualCast section)

* `echo`: Displays strings, variables or environment variables

* `env`: Permits you to list environment variables, but you can also launch a program with a specific environment set
  * Flags:
    * `-u $val` or `--unset=$val`: Destructs temporarly an environment variable named by $val
    * `-i` or `--ignore-environment`: Destructs temporarly all environment variable
    * `-0` or `--null`: Displays the list of environment variable without '\n' (You can't launch a program with this flag)
  * Examples:
    * `env` lists you the environment variables  
    * `env -i ls` launches ls command without any environment variables  
    * `env -u PATH bash` launches Bash without PATH variable

* `exit`: Exits the current shell

* `history`: Shows you the list of all previous commands entered. The most recent 500 commands are saved and restored between sessions

* `parser_ll`: It's a builtin that we have set up for explain the operation of a ll parser  
When you execute this builtin, you will enter an command input (like `ls test.c || echo "Failed" > result`) and the system show you the tree of the ll parsing

* `prompt`: Permits you to quickly change the prompt

* `set`: Sets a variable  
Example: `set test` creates a variable, named test, with no value  
`set test=value` creates a variable, named `test`, which contains `value`

* `setenv`: Sets a environment variable, unlike `set`, the value and the name are separate arguments and only one environment variable can be set at a time  
Exemple: `setenv test value` creates a variable named `test` with the value `value`

* `unalias`: Destructs an alias  
Example: `unalias ll` destructs the alias named 'll'

* `unset`: Destructs a variable  
Example: `unset test` destructs the variable named 'test'

* `unsetenv`: Destructs an environment variable, works like `unset`

* `where`: Shows all the possible meanings of a command

* `which`: Shows the actual first meaning of a command

### Configuration on the air
To simplify the configuration and the personalisation of the shell, we have set up an online configuration tool.

To start it, just execute the builtin `config`, the terminal shall prompt 'Server started' and a new page should be open on your navigator.
If it's not, make sure you have `google-chrome` or `firefox`.

On the first tab you can manage the environment variables.  
You can delete, update or add environment variable.

On the second tab you can manage the prompt.

On the third tab you can see the information in real time of your pc.  
You can see:
* The name of the distribution you use
* The name of the machine
* The platform you execute
* The version of the OS
* The name of the processor
* And the RAM usage

On the last tab you can use an integrate terminal to execute little and finite commands (like ls or cat).

You can stop the configuration by clicking on the cross.

### DualCast
DualCast is an exclusive technology which is between SSH and TeamViewer.

The concept is to connect two terminals, the first terminal will be a duplicate of the second terminal.  
DualCast can be useful in help cases. 

For example, if you face a problem and you ask a person to help you. Assuming that you provide him SSH access, when this person helps you, you can't see how he fixes the problem because SSH is opaque. With DualCast you can provide a temporary access to your server and you can see every command he enters.

To start a new DualCast session, just enter `dualcast start`. The system will provide you a token composed by 4 numbers.

In order to connect to a DualCast session, enter `dualcast connect $ip_address` where $ip_address is the ip of the computer you want to connect, after that, if the ip address is correct and if the person have entered `dualcast start`, the system will ask you the session token, you have to enter the token that you friend gave you.

For security reasons, if a person tries to connect to your DualCast server and enters a bad token, a message will be shown on the DualCast server.
          
During the connection, on the server side you can stop by pressing 'Enter', on the client side, you can stop by pressing 'Ctrl-C'.



