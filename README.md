# minishell
In this 42 project we create our own litte bash. This program is capable of parsing a prompt and launching executables.

## How to use it
Using ```make``` will create the executable ```minishell```.

Run it with: ```./minishell```

## Available cmds
Executables can be run from an absolute, relative or environmental PATH (``/bin/ls``, ``ls``) including arguments or options.
The symbols ``'`` and ``"`` work as in bash.

You can use redirections ``> >> <`` and pipes ``|`` ans Environment variables, including the return code ``$?``.
Signals like ``CTRL+C`` to interrupt, ``CTRL+\`` to quit and ``CTRL+D`` to throw an EOF. It works like in bash.

The Build-In function like ``echo``, ``pwd``, ``cd``, ``env``, ``export``, ``unset`` and ``exit`` are recoded in our minishell.
