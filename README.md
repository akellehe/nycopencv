nycopencv
===========

If you just wanna get started type:

```
mkdir /opt/nycopencv
git clone git@github.com:akellehe/nycopencv.git /opt/nycopencv/nycopencv
mkdir /opt/nycopencv/build
cd /opt/nycopencv/build
cmake /opt/nycopencv/nycopencv
make
```

Reasoning:

You should keep your source at 
```
/opt/nycopencv/nycopencv
```

It's a good practice to keep the build separate, so to build the package make a separate directory;

```
/opt/nycopencv/build
```

You can build the package  by `cd`-ing to there and running

```
cmake /opt/nycopencv/nycopencv; make
```

If you have a mac
-----------------

You'll see something along the lines of

```
Cound not find a package configuration file provided by "OpenCV" with any of the following names:

  OpenCVConfig.cmake
  opencv-config.cmake

```

Get homebrew! http://brew.sh/

Install it and then get cmake

```
brew install cmake
```

Once you've installed cmake get the opencv libraries (takes a second)

```
brew install homebrew/science/opencv
```

Then you can build normally.
