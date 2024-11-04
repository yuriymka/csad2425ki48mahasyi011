# Details about repository:
  This is a repository for performing laboratory work on the subject "Computer systems automated design". The main branch is develop. Branches named "feature/develop/<task number>" are created to perform laboratory work. 
Here will be the game tik-tac-toe 3x3 with communication schema SW(client) <-> UART <-> HW(server)

# Important:
1) All software must be under free license;
2) CY8CKIT-042 PSoC® 4 Pioneer Kit is recommended to use. In other cases,
students must provide HW to the lecturer for verification;
3) Estimation will be done in the rate system: whoever delivers the task first will
get the biggest point (students number in group), the last one will get 1 point.
And it will be maximum points. Each mistake in work will decrease these
points. If two or more work will be presented in one day then points will be
decreased as well (I work - maximum points, II work - maximum point minus
1, III work - maximum point minus 2 and so on). Task and report will have
different estimations.

# Task details:
## General requirements:
  The root folder should have next directories if required:
  1) **3party** - for all third party tools;
  2) **lib** - for libs;
  3) **build** - for generated code, binaries…;
  4) **ci** - for continuous integration scripts;
  5) **media** - for images and video;
  6) **config** - for configuration files;

MVC is the most common architecture design. But the student can use another
approach. It should have strong arguments about props and cons for the used
approach.

**Must be used:**
* Patterns;
* Data driven approach.

## Develop area:
* Hardware (HW) and Desktop software (SW)

## Menu:
Game should have a menu that allows to configure parameters

## Play modes:
* Man vs AI
* Man vs Man
* AI vs AI:
  * Random move
  * Win strategy

## Actions:
* New;
* Save;
* Load;

# Tasks by student:
1) **Student number:** 3
2) **Game:** tik-tac-toe 3x3
3) **Config format:** INI

# Technical details:
In this project i'm going to use Qt&C++. As for the HW I'm going to use Ardeino.
