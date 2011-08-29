# A simple chat server with unix sockets.

Author : Jaseem Abid <jaseemabid@gmail.com>

### Testing instructions

1. compile the server code `gcc server.c -o server -pthread`
2. compile the client code `gcc client.c -o client -pthread`
3. Run server `./server <port number>`. Eg: `./server 8089`
4. Run the client in a different terminal. `./client <server> <port>`. Eg: `./client localhost 8089`
5. Run any number of clients in different terminals
6. Send messages to user<n> in the format `<userid> <Message>`. Eg: `1 hello world`

## Report bugs at [github](https://github.com/jaseemabid/Networks-Lab/issues)

### References

* Original source of the demo codes : http://www.linuxhowtos.org/C_C++/socket.htm
* Threading tutorial : https://computing.llnl.gov/tutorials/pthreads/

Git for dummies
---------------

As the source code is handled by the version control system Git, it's useful to know some features used.

### Submodules ###

The repository uses submodules, which normally are handled directly by the Makefile, but sometimes you want to
be able to work with them manually.

Following are the steps to manually get the submodules:

1. `git clone https://jaseemabid@github.com/jaseemabid/Networks-Lab.git`
2. `git submodule init`
3. `git submodule update`

Or:

1. `git clone https://jaseemabid@github.com/jaseemabid/Networks-Lab.git`
2. `git submodule update --init`

Or:

1. `git clone --recursive https://jaseemabid@github.com/jaseemabid/Networks-Lab.git`

If you want to work inside a submodule, it is possible, but first you need to checkout a branch:

1. `cd src/docs`
2. `git checkout master`

After you've committed your changes to the submodule, you'll update the jquery project to point to the new commit,
but remember to push the submodule changes before pushing the new jquery commit:

1. `cd src/docs`
2. `git push origin master`
3. `cd ..`
4. `git add src/docs`
5. `git commit`

The makefile has some targets to simplify submodule handling:

#### `make update_submodules` ####

checks out the commit pointed to by jquery, but merges your local changes, if any. This target is executed 
when you are doing a normal `make`.

#### `make pull_submodules` ####

updates the content of the submodules to what is probably the latest upstream code.

#### `make pull` ####

make a `make pull_submodules` and after that a `git pull`. if you have no remote tracking in your master branch, you can
execute this command as `make pull REMOTE=origin BRANCH=master` instead.

### cleaning ###

If you want to purge your working directory back to the status of upstream, following commands can be used (remember everything you've worked on is gone after these):

1. `git reset --hard upstream/master`
2. `git clean -fdx`

### rebasing ###

For feature/topic branches, you should always used the `--rebase` flag to `git pull`, or if you are usually handling many temporary "to be in a github pull request" branches, run following to automate this:

* `git config branch.autosetuprebase local` (see `man git-config` for more information)

### handling merge conflicts ###

If you're getting merge conflicts when merging, instead of editing the conflicted files manually, you can use the feature
`git mergetool`. Even though the default tool `xxdiff` looks awful/old, it's rather useful.

Following are some commands that can be used there:

* `Ctrl + Alt + M` - automerge as much as possible
* `b` - jump to next merge conflict
* `s` - change the order of the conflicted lines
* `u` - undo an merge
* `left mouse button` - mark a block to be the winner
* `middle mouse button` - mark a line to be the winner
* `Ctrl + S` - save
* `Ctrl + Q` - quit

Questions?
----------

If you have any questions, please feel free to ask me at <jaseemabid@gmail.com>

