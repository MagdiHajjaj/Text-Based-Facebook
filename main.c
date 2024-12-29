/********* main.c ********
    Author = Magdi Hajjaj
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "a2_nodes.h"
#include "a2_functions.h"
//Commented out function 'read_CSV_and_create_users' for GitHub since spreadsheet not being included

int main()
{
    int choice;
    int manage_post_choice = 0;
    int manage_friend_choice = 0;
    bool friend_found;
    char username[31];
    char password[16];
    char new_friend_to_add[31];
    char friend_to_delete[31];
    char new_post_to_add[250];
    user_t *user_to_update;
    friend_t *current_friend; // to loop through user friends list.

    user_t *users= NULL;
    /*
    FILE *csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }
    // Parse CSV data and create users
    user_t *users = read_CSV_and_create_users(csv_file, 50);
    fclose(csv_file);
    */
    print_menu();
    while (true)
    {
        printf("Enter your choice: ");
        choice = get_input_usi();

        if (choice == 1)
        {
            printf("Enter a username: ");
            scanf("%s", username);
            lowercase(username);
            if (find_user(users, username) != NULL)
            {
                printf("\t****User already exists.****\n");
                printf("\t****Exsiting to main menu****\n\n");
                print_menu();
                continue;
            }
            printf("Enter an up to 15 characters password: ");
            while (true)
            {
                scanf("%s", password);
                if (strlen(password) >= 8)
                {
                    break;
                }
                else
                {
                    printf("Passowrd length must atleast be eight characters\n");
                    printf("Enter a different password: ");
                }
            }

            users = add_user(users, username, password);

            printf("\t  ****User Added!****\n\n");
            print_menu();
        }
        else if (choice == 2)
        {
            printf("\n-----------------------------------------------\n");
            printf("\t\tLogging in.\n");
            printf("-----------------------------------------------\n");
            printf("Enter a username: ");
            scanf("%s", username);
            lowercase(username);
            if (find_user(users, username) == NULL)
            {
                printf("\n-----------------------------------------------\n");
                printf("\t\tUser not found.\n");
                printf("-----------------------------------------------\n\n");
                print_menu();
                continue;
            }
            user_to_update = find_user(users, username);
            printf("Enter an up to 15 characters password: ");
            scanf("%s", password);
            if (strcmp(user_to_update->password, password) != 0)
            {
                printf("****Password not match****\n");
                print_menu();
                continue;
            }

            printf("***********************************************\n");
            printf("\t   Welcome %s:\n", user_to_update->username);
            printf("***********************************************\n");
            user_menu();
            while (true)
            {
                printf("Enter your choice: ");
                choice = get_input_usi();
                if (choice == 5)
                {
                    printf("Exsiting to main menu.\n");
                    print_menu();
                    break;
                }
                else if (choice == 4)
                {
                    char friend_name_to_display_post[31];
                    printf("Enter a friends name to display posts: ");
                    scanf("%s", friend_name_to_display_post);
                    lowercase(friend_name_to_display_post);
                    /*
                    If user wanted to choose the number of post to display.
                    int number_of_post = 0;
                    printf("Enter the number of posts you want displayed: ");
                    scanf("%d", &number_of_post);
                    */
                    friend_found = false;
                    current_friend = user_to_update->friends;
                    while (current_friend != NULL)
                    {
                        if (strcmp(current_friend->username, friend_name_to_display_post) == 0)
                        {
                            friend_found = true;
                            break;
                        }
                        current_friend = current_friend->next;
                    }
                    if (friend_found)
                    {
                        printf("\n-----------------------------------------------\n");
                        printf("\tDisplaying %s's posts\n", friend_name_to_display_post);
                        printf("-----------------------------------------------\n");
                        display_posts_by_n(user_to_update, 3, friend_name_to_display_post);
                    }
                    else
                    {
                        printf("****Sorry, %s and %s are not friends. You cannot view their post.****\n\n", user_to_update->username, friend_name_to_display_post);
                    }

                    printf("***********************************************\n");
                    printf("\t%s user menu:\n", user_to_update->username);
                    printf("***********************************************\n");
                    user_menu();
                }
                else if (choice == 3)
                {

                    printf("\n-----------------------------------------------\n");
                    printf("\tManaging %s's friends\n", user_to_update->username);
                    printf("-----------------------------------------------\n");
                    print_friend_menu();
                    while (true)
                    {
                        printf("Enter your choice: ");
                        manage_friend_choice = get_input_usi();
                        if (manage_friend_choice == 1)
                        {
                            printf("Enter a new friend's name: ");
                            scanf("%s", new_friend_to_add);
                            if (find_user(users, new_friend_to_add) == NULL)
                            {
                                printf("-----------------------------------------------\n");
                                printf("Friend's name (%s) does not have a facebook account\n", new_friend_to_add);
                                printf("-----------------------------------------------\n");
                                printf("\nFriend's menu:\n");
                                print_friend_menu();
                                continue;
                            }
                            add_friend(users, user_to_update, new_friend_to_add);

                            printf("\n****Friend added to the list.****\n");
                            printf("\nFriend's menu:\n");
                            print_friend_menu();
                        }
                        else if (manage_friend_choice == 2)
                        {
                            printf("\n  ****%s's friends list.****", user_to_update->username);
                            printf("\n-----------------------------------------------\n");
                            display_user_friends(user_to_update);
                            printf("-----------------------------------------------\n");
                            if (user_to_update->friends == NULL)
                            {
                                print_friend_menu();
                                continue;
                            }
                            printf("Enter a friend's name to delete: ");
                            scanf("%s", friend_to_delete);
                            if (delete_friend(user_to_update, friend_to_delete))
                            {
                                printf("%s deleted successfully.\n", friend_to_delete);

                                printf("\n****Updated %s's friends list.****", user_to_update->username);

                                printf("\n-----------------------------------------------\n");
                                display_user_friends(user_to_update);
                                printf("-----------------------------------------------\n");
                                printf("\nFriend's menu:\n");
                            }
                            else
                            {
                                printf("Invalid friend's name.\n");
                            }
                            print_friend_menu();
                        }
                        else if (manage_friend_choice == 3)
                        {
                            printf("***********************************************\n");
                            printf("\t%s user menu:\n", user_to_update->username);
                            printf("***********************************************\n");
                            user_menu();
                            break;
                        }
                        else
                        {
                            printf("Invalid Choice. Please try again\n");
                        }
                    }
                }
                else if (choice == 2)
                {

                    printf("\n-----------------------------------------------\n");
                    printf("\tManaging %s's posts\n", user_to_update->username);
                    printf("-----------------------------------------------\n");
                    (user_to_update->posts == NULL) ? printf("Note: No posts available for %s\n", user_to_update->username) : (void)0;
                    print_post_menu();
                    while (true)
                    {
                        printf("Enter your choice: ");
                        manage_post_choice = get_input_usi();
                        if (manage_post_choice == 1)
                        {
                            printf("Enter your post content: ");
                            scanf(" %[^\n]s", new_post_to_add);
                            add_post(user_to_update, new_post_to_add);
                            printf("\n-----------------------------------------------\n");
                            printf("\t%s's posts\n", user_to_update->username);
                            display_all_user_posts(user_to_update);
                            printf("-----------------------------------------------\n\n");
                            print_post_menu();
                        }
                        else if (manage_post_choice == 2)
                        {
                            if (delete_post(user_to_update))
                            {
                                printf("****Recent post deleted!****\n");
                                printf("\n\t****New updated posts!****\n");
                                printf("-----------------------------------------------\n");
                                printf("\t%s's posts\n", user_to_update->username);
                                display_all_user_posts(user_to_update);
                                printf("-----------------------------------------------\n\n");
                            }
                            else
                            {
                                printf("****No Post to be deleted****\n");
                            }
                            print_post_menu();
                        }
                        else if (manage_post_choice == 3)
                        {
                            printf("***********************************************\n");
                            printf("\t%s user menu:\n", user_to_update->username);
                            printf("***********************************************\n");
                            user_menu();
                            break;
                        }
                        else
                        {
                            printf("Invalid Choice. Please try again\n");
                        }
                    }
                }
                else if (choice == 1)
                {
                    printf("Enter the old password: ");
                    scanf("%s", password);

                    if (strcmp(user_to_update->password, password) == 0)
                    {
                        printf("Enter a new password. Up to 15 characters: ");
                        while (true)
                        {
                            scanf("%s", password);
                            if (strlen(password) >= 8)
                            {
                                break;
                            }
                            else
                            {
                                printf("Passowrd length must atleast be eight characters\n");
                                printf("Enter a different password: ");
                            }
                        }

                        strcpy(user_to_update->password, password);
                        printf("\t****Password changed!****\n");
                    }
                    else
                    {
                        printf("The passwords do not match.\n");
                    }
                    printf("***********************************************\n");
                    printf("\t%s user menu:\n", user_to_update->username);
                    printf("***********************************************\n");
                    user_menu();
                }
                else
                {
                    printf("Invalid Choice. Please try again\n");
                }
            }
        }
        else if (choice == 3)
        {
            teardown(users);
            printf("Thank you for using Facebook. Goodbye!\n");
            break;
        }
        else
        {
            printf("Invalid choice. Please select a valid option.\n");
                }
    }
}
