nycopencv
===========

If you just wanna get started type:

```
mkdir /opt/nycopencv
git clone git@github.com:nycopencv/nycopencv.git /opt/nycopencv
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
