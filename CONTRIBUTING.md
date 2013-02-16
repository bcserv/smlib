# Contribution guidelines


**Index of contents**
* What chances do I have to add new code to smlib ?
	* Through pull requests
	* Write/Push access (direct committing)
* General rules
* Checklist before submitting pull requests / committing new code
* Consistent code style
	* smlib code style example

## What chances do I have to add new code to smlib ?

### Through pull requests

If you have a Github account, you can make one.
This will require you to fork this project to your own user first, Do/commit the changes there and create a new pull request from the master branch of your smlib repository to here.

[Here is a more detailled description on how to do it.](https://help.github.com/articles/using-pull-requests)

Also: read the rest of this document first.

### Write/Push access (direct committing)

We give people push access who have already done some successful pull requests.

[Create an issue](https://github.com/bcserv/smlib/issues/new), if you feel you would be a good team member/contributor.

## General rules

* Only add game-independent code (try to find the lowest common denominator between games), if a feature is only supported by one game, create a new file/namespace for this specific game
* Use a (to this project) consistent code style
* Don't add code that uses virtual offsets/function signatures/symbols (we don't want to maintain them)
* Write long, self-explaining function/variable names.
* If you add code from other people, don't forget to mention that in a function annotation or comment
* Document all functions with annotations (have a look at other functions)
* Comment your code (That's also useful for yourself, you will forget about things after some time)
* Add used function `#include` dependencies at top to ensure single smlib include files can be included in plugins without having to include the whole `<smlib>`
* If you are working on a bigger feature in smlib, that will require multiple commits to be made, consider creating a new feature branch ("feature-yourfeaturename") and make a pull request when you are done to merge it with the master
* Write re-usable, capsulated, readable, clean code
* Don't use the function "ServerCommand", unless you have a really really really good reason to do so.
* Don't add code that messes with the client's settings (ie. console command hacks)


## Checklist before submitting pull requests / committing new code

* Rules: read?
* Consistent code style
* Documentation written (function annotations, comments)
* Add new functions to test_compile-all.sp to make sure the even compile without warnings.
* Write a summary of what you did into the first commit message line, and more detailed information into the next lines.
* Avoid pushing merge commits (within the same branch), they pollute the histoy. Use "git rebase" to stack commits. [Here](http://randyfay.com/content/simpler-rebasing-avoiding-unintentional-merge-commits) is a good tutorial.

## Consistent code style

* We use tabs for intendation
* We use whitespace for aligning code in-line
* Use long, self-explaining variable/function names
* ALWAYS use `{` `}` brackets
* Don't use abbrevations anywhere in function/variable names etc., except they are well-known (like "HTTP")
* Use newlines to group your code into logical parts
* Write names in [camelCase](https://www.google.at/?q=camelCase)
* Make a line break if the line is already too long (we don't have a specific width)

### smlib code style example
```php
/**
 * Returns the index for the first occurance of the given value.
 * If the value cannot be found, -1 will be returned.
 *
 * @param hard     Set this to true to slap the players hard.
 * @return         True if the slapping was successful, false otherwise
 */
function SlapAllPlayers(bool:hard=true)
{ // Function opening bracket on next line
	var var1         = 1; // Variables start with a lower case letter
	var anotherVar2  = 2;

	for (new client=1; client <= MaxClients; client++) { // for, while, do, switch etc. brackets on same line
	
		if () { // if, else brackets on same line
			 // Some code
		}
		else {
			// Some code
		}
	}
}
```
