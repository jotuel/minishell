> [!NOTE]
> Created with @Tonttu84 as part of our studies at Hive.

It is quite well functioning command interpreter. The limitations (time and what we were literally allowed to do) of the projects means it won't really be able to replace any production ready shell. And because some things are set at compile time, rather than runtime, it might have some not expected behaviour on multi-user systems. Only small thing like the prompt text though.

> [!IMPORTANT]
> *, &&, ||, help, few builtins and some POSIX enviroment things are completely missing.

To use it:
```
git clone https://github.com/jotuel/minishell msh
cd msh
make
./minishell
```

> [!CAUTION]
> Only tested with Linux. Also by design it lacks some signal handlers which can cause issues with readline. 

It is quite rare though to get such signals.
