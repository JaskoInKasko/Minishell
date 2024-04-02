#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void display_prompt()
{
    printf("$");
}

int main()
{
    char	*input;
	char	*user_input;

    while (1)
	{
        display_prompt();
        input = readline("");
        if (strcmp(input, "exit") == 0)
		{
            printf("Exiting the shell...\n");
            free(input);
            break;
        }
		if (strncmp(input, "echo", 4) == 0)
		{
			user_input = (input + 5);
            printf("%s\n", user_input);
		}
		add_history(input);
        free(input);
    }
	//rl_clear_history();
    return 0;
}
