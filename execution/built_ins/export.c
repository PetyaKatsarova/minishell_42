/*
ENV
Prints only exported variables
exported variables are environment variables that the shell passes to child processes.
VAR1=hello       # normal shell variable (not exported)
export VAR2=world  # exported to child processes
env              # shows VAR2, not VAR1
If you run a program (e.g. ls, vim, or gcc), only exported variables are visible to that program!!NB!!

env:
In simple KEY=value format
PATH=/usr/bin:/bin
HOME=/home/petya
----------
EXPORT
Prints all exported variables, including those without value
declare -x VAR="value"
declare -x PATH="/usr/bin:/bin"

env	    active variables	    KEY=value
export	exportable vars(all) 	declare -x KEY="..."

| Feature / Behavior             | `env`                                     | `export`                                      |
|-------------------------------|-------------------------------------------|-----------------------------------------------|
| **Primary Purpose**           | Print or temporarily modify environment   | Mark variables to be inherited by child procs |
| **Without Arguments**         | Prints current exported variables         | Prints all exported vars (even empty)         |
| **With `VAR=value`**          | Temporarily sets for a command            | Adds/modifies in current shell permanently    |
| **Output Format**             | `KEY=value`                               | `declare -x KEY="value"`                      |
| **Includes empty vars**       | ❌ Only vars with values                  | ✅ Shows vars even without value              |
| **Command execution**         | `env VAR=value command` is valid          | `export VAR=value` doesn't run a command      |
| **Temporary effect**          | ✅ Only affects that command             | ❌ Persists in current shell                  |
| **Use in scripts**            | Often for one-time command env setup      | For global shell config or persistent exports |

*/