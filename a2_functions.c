/*****************
    Author = Magdi Hajjaj
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <ctype.h>
#include "a2_nodes.h"
#include "a2_functions.h"
/*
   Updated add_friend function to include the all_users list as a parameter.
   Ensures that only registered users from the all_users list can be added as friends.
    Commented out function 'read_CSV_and_create_users' for GitHub since spreadsheet not being included
*/
/*
   Function that creates a new user and adds it to a sorted (ascending order) linked list at
   the proper sorted location. Return the head of the list.
*/
user_t *add_user(user_t *users, const char *username, const char *password)
{

    user_t *newnode = malloc(sizeof(user_t));
    assert(newnode != NULL);
    strcpy(newnode->username, username);
    strcpy(newnode->password, password);
    newnode->next = NULL;
    newnode->friends = NULL;
    newnode->posts = NULL;

    if (users == NULL || strcmp(newnode->username, users->username) < 0)
    {

        newnode->next = users;
        return newnode;
    }

    user_t *current = users;
    user_t *prev = NULL;
    while (current != NULL && strcmp(current->username, newnode->username) < 0)
    {

        prev = current;
        current = current->next;
    }
    newnode->next = current;
    prev->next = newnode;

    return users;
}
/*
   Function that searches if the user is available in the database
   Return a pointer to the user if found and NULL if not found.
*/
user_t *find_user(user_t *users, const char *username)
{

    user_t *user_location = users;
    for (; user_location != NULL; user_location = user_location->next)
    {
        if (strcmp(user_location->username, username) == 0)
        {

            return user_location;
        }
    }
    return NULL;
}
/*
   Function that creates a new friend's node.
   Return the newly created node.
*/
friend_t *create_friend(const char *username)
{

    friend_t *new_friend = malloc(sizeof(friend_t));
    assert(new_friend != NULL);
    strcpy(new_friend->username, username);
    new_friend->next = NULL;
    return new_friend;
}
/*
   Function that links a friend to a user. The friend's name should be added into
   a sorted (ascending order) linked list.
*/
void add_friend(user_t *all_users, user_t *user, const char *friend)
{
    user_t *friend_profile = find_user(all_users, friend);
    if (friend_profile == NULL)
    {
        printf("-----------------------------------------------\n");
        printf("Friend's name (%s) does not have a facebook account\n", friend);
        printf("-----------------------------------------------\n");
        return;
    }
    friend_t *friend_to_add = create_friend(friend);
    friend_to_add->posts = &(friend_profile->posts);
    if (user->friends == NULL || strcmp(friend_to_add->username, user->friends->username) < 0)
    {

        friend_to_add->next = user->friends;
        user->friends = friend_to_add;
        return;
    }

    friend_t *current, *prev;
    for (current = user->friends, prev = NULL; current != NULL && strcmp(current->username, friend_to_add->username) < 0;
         prev = current, current = current->next)
    {
    }
    prev->next = friend_to_add;
    friend_to_add->next = current;
}
/*
   Function that removes a friend from a user's friend list.
   Return true of the friend was deleted and false otherwise.
*/
_Bool delete_friend(user_t *user, char *friend_name)
{

    friend_t *current = user->friends;
    friend_t *prev = NULL;
    while (current != NULL)
    {
        if (strcmp(current->username, friend_name) == 0)
        {

            if (prev == NULL)
            {
                user->friends = current->next;
            }
            else
            {
                prev->next = current->next;
            }

            free(current);
            current = NULL;
            return true;
        }
        prev = current;
        current = current->next;
    }

    if (current == NULL)
    {
        return false;
    }
}

/*
   Function that creates a new user's post.
   Return the newly created post.
*/
post_t *create_post(const char *text)
{

    post_t *new_post = malloc(sizeof(post_t));
    assert(new_post != NULL);
    strcpy(new_post->content, text);
    new_post->next = NULL;
    return new_post;
}
/*
   Function that adds a post to a user's timeline following a stack.
*/
void add_post(user_t *user, const char *text)
{

    post_t *post_to_add = create_post(text);
    post_to_add->next = user->posts;
    user->posts = post_to_add;
}

/*
   Function that removes a post from a user's list of posts.
   Return true if the post was deleted and false otherwise.
*/
_Bool delete_post(user_t *user)
{
    if (user->posts == NULL)
    {
        return false;
    }
    post_t *post_to_delete = user->posts;
    user->posts = post_to_delete->next;
    free(post_to_delete);
    post_to_delete = NULL;
    return true;
}

/*
   Function that  displays a specific user's posts (All posts)
*/
void display_all_user_posts(user_t *user)
{
    if (user == NULL || user->posts == NULL)
    {
        printf("No posts available.\n");
        return;
    }

    int counter = 0;
    post_t *current_post = user->posts;
    while (current_post != NULL)
    {
        counter++;
        current_post = current_post->next;
    }
    current_post = user->posts;
    while (current_post != NULL)
    {
        printf("%d - ", counter);
        printf("%s\n", current_post->content);
        current_post = current_post->next;
        counter--;
    }
}

/*
   Function that displays a specific user's friends (All friends)
*/
void display_user_friends(user_t *user)
{
    int counter = 1;
    friend_t *current_friend = user->friends;
    if (user == NULL || user->friends == NULL)
    {
        printf("No Friends Available.\n");
        return;
    }
    while (current_friend != NULL)
    {
        printf("%d-  %s\n", counter, current_friend->username);
        counter++;
        current_friend = current_friend->next;
    }
}

/*
   Function that displays "number" of posts for a given user.
   After displaying "number" posts, it prompts if you want to display
   more posts.
   If there are no more post or the user types “n” or “N”, the function returns.
*/
void display_posts_by_n(user_t *user, int number, char *friend_name_to_display_post)
{
    friend_t *current_friend = user->friends;
    post_t **friends_post = NULL;
    while (current_friend != NULL)
    {
        if (strcmp(current_friend->username, friend_name_to_display_post) == 0)
        {
            friends_post = current_friend->posts;
            break;
        }
        current_friend = current_friend->next;
    }

    char user_choice;
    int total_count = 1;

    while ((*friends_post) != NULL)
    {
        for (int i = 0; i < number && friends_post != NULL; i++, *friends_post = (*friends_post)->next)
        {

            printf("%d - %s\n", total_count, (*friends_post)->content);
            total_count++;
        }
        if ((*friends_post) != NULL)
        {
            printf("Do you you want to display more posts (Y/N) ? ");
            scanf(" %c", &user_choice);
            if (tolower(user_choice) == 'y')
            {
                printf("\n****Displaying %s next %d posts****\n", friend_name_to_display_post, number);
            }
            else
            {
                printf("Exiting to main menu.\n");
                break;
            }
        }
    }
    if ((*friends_post) == NULL)
    {
        printf("\n****No more posts available for this user****\n\n");
        return;
    }
}


/*
   Function that free all users from the database before quitting the application.
*/
void teardown(user_t *users)
{
    while (users != NULL)
    {
        user_t *temp = users;
        users = users->next;

        while (temp->friends != NULL)
        {
            friend_t *temp_friend = temp->friends;
            temp->friends = temp->friends->next;
            free(temp_friend);
            temp_friend = NULL;
        }

        while (temp->posts != NULL)
        {
            post_t *temp_post = temp->posts;
            temp->posts = temp->posts->next;
            free(temp_post);
            temp_post = NULL;
        }

        free(temp);
        temp = NULL;
    }
}

/*

   Function that prints the main menu with a list of options for the user to choose from
*/
void print_menu()
{
    printf("***********************************************\n");
    printf("\tWelcome to Text-Based Facebook\n");
    printf("***********************************************\n\n");

    printf("***********************************************\n");
    printf("\t\tMAIN MENU:\n");
    printf("***********************************************\n");
    printf("1. Register a new user\n");
    printf("2. Login with existing user's information\n");
    printf("3. Exit program\n");
}

/*
   ******** DONT MODIFY THIS FUNCTION ********
   Function that reads users from the text file.
   IMPORTANT: This function shouldn't be modified and used as is
   ******** DONT MODIFY THIS FUNCTION ********
*/




/*
   
user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
    srand(time(NULL));
    user_t *users = NULL;
    char buffer[500];
    fgets(buffer, sizeof(buffer), file); // Read and discard the header line
    int count = 0;
    for (int i = 0; i < num_users; i++)
    {
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

        char *token = strtok(buffer, ",");
        char *token2 = strtok(NULL, ",");
        users = add_user(users, token, token2);
        char *username = token;

        token = strtok(NULL, ",");

        user_t *current_user = users;
        for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
            ;

        while (token != NULL && strcmp(token, ",") != 0 && count < 3)
        {
            if (strcmp(token, " ") != 0)
            {
                add_friend(users, current_user, token);
            }
            token = strtok(NULL, ",");
            count++;
        }
        count = 0;

        // token = strtok(NULL, ",");
        while (token != NULL && strcmp(token, ",") != 0)
        {
            add_post(current_user, token);
            token = strtok(NULL, ",");
        }
    }
    return users;
}
*/
// Extra functions' Prototypes/Declarations go here

unsigned short int get_input_usi(void)
{
    short int user_input;
    int result; // Variable to hold the return value of scanf to check if input was successfully read
    do
    {
        result = scanf("%hd", &user_input);
        if (result != 1 || user_input < 0 || user_input > 32767)
        {
            printf("--------------------------------------------------------\n");
            printf("The value entered is invalid. Please enter a valid integer: ");
            while (getchar() != '\n')
                ;
        }
        else
        {
            break;
        }
    } while (true);
    return user_input;
}
void user_menu()
{

    printf("1. Manage profile (change password)\n");
    printf("2. Manage posts (add/remove)\n");
    printf("3. Manage friends (add/remove)\n");
    printf("4. Display friend's posts\n");
    printf("5. Exit\n");
}
void print_post_menu()
{
    printf("1. Add a new post\n");
    printf("2. Remove a post\n");
    printf("3. Return to main menu\n");
}
void print_friend_menu()
{
    printf("1. Add a new friend\n");
    printf("2. Remove a friend\n");
    printf("3. Return to main menu\n");
}
void lowercase(char *str)
{
    while (*str)
    {
        *str = tolower(*str);
        str++;
    }
}
