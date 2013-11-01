jGPC - Java binding for [General Poligon Clipper library](http://www.cs.man.ac.uk/~toby/gpc/)
=======================================================

License
-------
Distributed under the LGPLv3 License. Copyright (c) 2013 Sergey Yungman (aka komelgman)


Example
-------

```Java
GpcPolygon poly1 = new GpcPolygon(
        createContour(50, 50, 50, 300, 300, 300, 300, 150, 400, 150, 400, 50),
        createContour(350, 200, 350, 400, 450, 400, 450, 200),
        createHole(250, 100, 250, 200, 100, 200, 100, 100)
);

GpcPolygon poly2 = new GpcPolygon(
    createContour(150, 150, 150, 300, 400, 300, 400, 150)
);

GeometryTransfer clip = Gpc.clip(GpcOperation.DIFF, poly1, poly2);
Geometry[] geometry = clip.get();
GpcPolygon opResult = new GpcPolygon(geometry);
```

See complete code in usage/Main.java
