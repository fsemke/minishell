# minishell
In this 42 project we create our own litte bash. This program is capable of parsing a prompt and launching executables.

## How to use it
Using ```make``` will create the executable ```minishell```.

Run it with: ```./minishell```

## Available cmds
Executables can be run from an absolute, relative or environmental PATH (``/bin/ls``, ``ls``) including arguments or options.
The symbols ``'`` and ``"`` work as in bash.
We have also build a history that you can call with ``history``.

You can use redirections ``> >> <`` and pipes ``|``.
Environment variables, including the return code ``$?`` are also working.
Signals like ``CTRL+C`` to interrupt, ``CTRL+\`` to quit and ``CTRL+D`` to throw an EOF.

The Build-In function like ``echo``, ``pwd``, ``cd``, ``env``, ``export``, ``unset`` and ``exit`` are recoded in our minishell.
All this stuff should work like the real bash.
