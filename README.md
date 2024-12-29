# Text-Based Social Media Application

## Overview
A text-based social media platform built in **C** that allows users to register, manage their profiles, add/remove friends, post updates, and display posts. The app uses **linked lists** to manage users and friends, and a **stack** for managing user posts. It includes a menu-driven interface with input validation.

## Features
- **User Registration**: Users can create an account with a username and password.
- **Profile Management**: Users can change their password securely.
- **Friend Management**: Users can add or remove friends from their profile.
- **Post Management**: Users can add or remove posts, with posts stored in a stack (LIFO).
- **Display Posts**: View the most recent posts from a user.
- **Input Validation**: Ensures all user input is valid and handles errors gracefully.

## Requirements
- C Compiler (e.g., GCC)
- **Standard Libraries**: `<stdio.h>`, `<string.h>`, `<stdlib.h>`

## Setup and Usage
1. Clone or download the repository.
2. Open the terminal and navigate to the project folder.
3. Compile the program:
   ```bash
   gcc -g *.c -o social_media_app
4. Run the application:
   ```bash
   ./social_media_app
    ```
5. Follow the on-screen instructions to interact with the app
## Functions

### User Management
- **add_user()**: Creates a new user and adds them to the sorted linked list of users.
- **find_user()**: Searches for a user by their username.
- **delete_friend()**: Removes a friend from the user's friend list.
- **change_password()**: Allows a user to change their password.

### Friend Management
- **add_friend()**: Adds a new friend to the user's friend list, ensuring the friend is a registered user.
- **create_friend()**: Creates a new friend node.
- **display_user_friends()**: Displays all friends of a user.

### Post Management
- **add_post()**: Adds a new post to a user's timeline (stack).
- **delete_post()**: Removes the most recent post from the user's stack.
- **create_post()**: Creates a new post.
- **display_all_user_posts()**: Displays all posts of a user.
- **display_posts_by_n()**: Displays a specified number of posts and prompts the user to continue displaying more.

### Miscellaneous
- **teardown()**: Frees all user data and cleans up the memory.
- **print_menu()**: Displays the main menu with options for the user to choose from.
- **user_menu()**: Displays the user profile management menu.
- **print_post_menu()**: Displays the post management menu.
- **print_friend_menu()**: Displays the friend management menu.
- **lowercase()**: Converts a string to lowercase.
## Example Usage

### Main Menu:
  ```plaintext
  ***********************************************
          Welcome to Text-Based Facebook
  ***********************************************

  ***********************************************
                  MAIN MENU:
  ***********************************************
  1. Register a new user
  2. Login with existing  users information
  3. Exit program
  Enter your choice: 1 
  ```
### Sample Input and Output:
```plaintext
Enter an up to 15 characters password: 123456  
Password length must at least be eight characters  
Enter a different password: 12345678  
            ****User Added!****

***********************************************
        Welcome to Text-Based Facebook
***********************************************

***********************************************
              MAIN MENU:
***********************************************
1. Register a new user  
2. Login with existing  users information  
3. Exit program  
Enter your choice:
```

## License

[MIT](https://choosealicense.com/licenses/mit/)

Copyright (c) 2024 Magdi Hajjaj

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
