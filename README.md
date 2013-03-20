MacOSX-broken-symlink-finder
============================

Contains a program which can be used to find the sort of broken symlinks that frequently occur on Mac OS X Mountain Lion if your hard drive partition is over 2TB.

Once you have compiled the program, issue the following find command:

    find / -xdev -type l -type l -exec ./checkSymlink {} \;
    
You must issue the find command using root privileges from the directory containing the checkSymlink program.

This can take quite a while.

The symlinks that this program finds are probably but not necessarily broken.  Use some judgement when fixing them.

Note: if you do not know how to compile this program then you should probably seek assistance from someone who does (do NOT contact the author).

IMPORTANT:

This program comes with no warrantees of any kind.
Use at your own risk.

EVEN MORE IMPORTANT:

Be VERY careful when 'fixing' the links that this program reports as you can easily make a bad situation much much worse.
