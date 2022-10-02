#include <stdio.h>
#include <stdlib.h>

#include "cmdline.h"

#include "vty.h"

static CliExRes_t statusFunction         (CliState_t *state);
static CliExRes_t sumFunction            (CliState_t *state);

const char cmd_status[] = "status";
const char cmd_help_status[] = "Prints current system status";

const Command_t cmdListNormal[] =
{
  {cmd_help,            cmd_help_help,            helpFunction,                0},
  {cmd_history,         cmd_help_history,         historyFunction,             0},
  {cmd_status,          cmd_help_status,          statusFunction,              0},
  {cmd_enable,          cmd_help_enable,          enableFunction,              0},
  {"sum",              "Adds the given numbers",  sumFunction,                 CLI_STATE_MAX_ARGC},
  {NULL               , NULL,                     NULL,                        0}
};

const Command_t cmdListEnable[] =
{
  {cmd_help,            cmd_help_help,            helpFunction,                0},
  {cmd_history,         cmd_help_history,         historyFunction,             0},
  {cmd_status,          cmd_help_status,          statusFunction,              0},
  {cmd_disable,         cmd_help_disable,         enableFunction,              0},
  {NULL               , NULL,                     NULL,                        0}
};

const Command_t cmdListConfigure[] =
{
  {cmd_help,            cmd_help_help,            helpFunction,                0},
  {cmd_history,         cmd_help_history,         historyFunction,             0},
  {cmd_status,          cmd_help_status,          statusFunction,              0},
  {cmd_enable,          cmd_help_enable,          enableFunction,              0},
  {NULL               , NULL,                     NULL,                        0}
};


static CliExRes_t statusFunction(CliState_t *state)
{
	fprintf(state->strOut, "Status.... not implemented yet\r\n");
	//printStatus(state->myStdInOut);
    return OK_SILENT;
}

static CliExRes_t sumFunction(CliState_t *state)
{
	int suma = 0;
	for (int i = 1; i < state->argc; i++)
	{
		suma += atoi(state->argv[i]);
	}
	fprintf(state->strOut, "The sum of %d given numbers is equal to %d\r\n", state->argc-1, suma);


	//printStatus(state->myStdInOut);
    return OK_SILENT;
}
