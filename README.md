# Chomusuke

This is a test project for learning SFML.



**1. Clone:**

```
git clone --recursive https://github.com/ginpachiSensei/TestGame.git
```
If cloned without recusive use `git submodule update --init` to fix
This project imports it's dependency on SFML via a git submodule in the ext folder.

<dl>
    <dt> Requirements<dt>
    <dd style='color:red'> CMake -- required to build this project </dd>
<dl>

**2. Build project** 
```console
cd TestGame
mkdir build && cd build
cmake ..
./TestGame
```
SFML can be found http://www.sfml-dev.org
