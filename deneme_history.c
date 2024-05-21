// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   deneme_history.c                                   :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mtoktas <mtoktas@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/05/21 16:30:08 by mtoktas           #+#    #+#             */
// /*   Updated: 2024/05/21 17:01:15 by mtoktas          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <signal.h>
// #include <readline/readline.h>
// #include <readline/history.h>

// void handle_signal(int sig)
// {
//     if (sig == SIGINT)
//     {
//         printf("\nCtrl+C pressed, exiting...\n");
//         exit(0);
//     }
//     else if (sig == SIGQUIT)
//     {
//         printf("\nCtrl+\\ pressed, exiting...\n");
//         exit(0);
//     }
//     // Diğer sinyaller için gerekli işlemler eklenebilir.
// }

// void init_signal(void)
// {
//     signal(SIGINT, handle_signal);
//     signal(SIGQUIT, handle_signal);
//     // Diğer sinyaller için gerekli işlemler burada eklenebilir.
// }

// int main(int ac, char **av, char **envp)
// {
//     (void)ac;
//     (void)av;
//     (void)envp;

//     init_signal();
//     using_history(); // Readline history işlevlerini kullanmak için gerekli

//     while (1)
//     {
//         char *line = readline("deneme_history$>");

//         if (line && *line)
//         {
//             add_history(line);
//             printf("line : %s\n", line);
//         }
//         else if (line)
//         {
//             free(line);
//             continue;
//         }

//         free(line);

//         // Geçmiş girdileri gösterme işlemi
//         HISTORY_STATE *history_state = history_get_history_state();

//         history_set_history_state(history_state);
//         free(history_state);
//     }

//     return 0;
// }



