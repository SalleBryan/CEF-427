# Mini-OS Feature Test Commands

This guide provides a sequence of shell and CLI commands you can run to demonstrate
all major mini-OS features (kernel boot/CLI, process management, scheduler,
memory allocator, filesystem, and built-in apps).

## Build and start the simulator

```sh
make
./mini_os
```

## CLI walkthrough (type inside `mini_os`)

```text
help
ps
create alpha
create beta
ps
schedule
schedule
mem
alloc 1 4
alloc 2 2
mem
free 1
mem
touch notes.txt
touch log.txt
ls
run echo
Hello from the echo app!
run calc
3 9
run sleep
3
schedule
exit
```

## Notes
- The `run echo`, `run calc`, and `run sleep` commands will prompt for input.
  Provide the input lines shown immediately after each command.
- If you want to demonstrate the scheduler with many processes, you can repeat
  `create <name>` up to the maximum process count, then call `schedule` to see
  round-robin behavior.
