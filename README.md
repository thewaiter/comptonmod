# comptonmod

Compton module for the Moksha desktop.

This module adds compositing features to the Mosksha desktop. Enlightenment 17 had native compositing but it was rather unstable and had issues. The Bodhi team removed the featured and recommended users that wanted or need that functionality use a third party compositor. Over time it became apparent that we needed an easy way for beginning users to install and set up compositing. So the compton module was born, originally using compton as a backend. We later switched to [Picom](https://github.com/yshui/picom) to provide a light weight compositor. For Historical reasons this module is still called the compton module even though the backend it uses is Picom, a [fork of Compton](https://github.com/yshui/picom/blob/next/History.md).

## Usage

## Dependecies

* [EFL](https://www.enlightenment.org/download)
* [Moksha](https://github.com/JeffHoogland/moksha)
* [Picom](https://github.com/yshui/picom)

## Installation

It is recommended Bodhi users install from Bodhi's repo:

```ShellSession
sudo apt update
sudo apt install moksha-module-compton
```

Other users need to compile the code:

First install all the needed dependencies. Note this includes not only EFL but the EFL header files. If you have compiled and installed EFL and Moksha from source code this should be no problem.

Then the usual:

```ShellSession
meson . build
ninja -C build
sudo ninja -C build
```

## Reporting bugs

Please use the GitHub issue tracker for any bugs or feature suggestions:

>[github.com/thewaiter/comptonmod/issues](https://github.com/thewaiter/comptonmod/issues)

## Contributing

Help is always Welcome, as with all Open Source Projects the more people that help the better it gets!
More translations would be especially welcome and much needed.

Please submit patches to the code or documentation as GitHub pull requests!

Contributions must be licensed under this project's copyright (see COPYING).
