CatGenius 2
========

This is a rewriten codebase from the [CatGenius project](https://github.com/CatGenius/catgenius)

The reason of rewriting this code was that I had some issue with the original project, instead of trying to debug it,
 given the complexity it had reached and use of deprecated compiler, I decided to rewrite it with a simpler logic. 

Many functionalities of the original project is not implemented yet.

Currently it is tested with a catgenie120 (the currently sold version) and a PIC16F1939 but should work seamlessly on the original PIC16F877

This version works with MPLab X IDE and the current XC8 compiler 

----

Todo:
---

- Implement the cat sensor
- Implement the storage of the settings to the NVM
- Implement a software stop on the overheat signal
- Implement further menu settings for dry cycle


----

Known Issues:
---

- The timed process of cleaning doesn't start but is probably fix (tests ongoing).

----

File Structure:
---

- main 		- original startup
- catgenie120	- hardware related
- tasks		- contains all the task related like moving things, checking things
- process	- control the processes related of cleaning
- businesslogic	- control all the triggers for cleaning and user interface actions