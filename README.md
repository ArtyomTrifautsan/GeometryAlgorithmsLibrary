# Геометрические алгоритмы на C++

![C++20](https://img.shields.io/badge/language-C++20-blue.svg)
![Google Test](https://img.shields.io/badge/testing-GoogleTest-red.svg)

Данный репозиторий содержит реализацию [геометрических алгоритмов в 2D и 3D](./GeometryCore/Algorithms/), а также [кривых Безье](./GeometryCore/Curves/).

### Реализованные геометрические алгоритмы в 2D:
1. [Взаимное расположение точки и замкнутого многоугольника](./GeometryCore/Algorithms/PointPolygonLocation2.h) (проверка нахождения точки внутри многоугольника).
2. [Расстояние от точки до отрезка](./GeometryCore/Algorithms/PointSegmentDistance2.h).
3. [Расстояние от точки до точки](./GeometryCore/Algorithms/PointPointDistance2.h).
4. [Пересечение двух линий](./GeometryCore/Algorithms/LineLineIntersection2.h).
5. [Пересечение двух отрезков](./GeometryCore/Algorithms/SegmentSegmentIntersection2.h).
6. [Пересечение луча и отрезка](./GeometryCore/Algorithms/RaySegmentIntersection2.h).

### Реализованные геометрические алгоритмы в 3D:
1. [Пересечение луча и треугольника](./GeometryCore/Algorithms/RayTriangleIntersection3.h).
2. [Расстояние между двумя отрезками](./GeometryCore/Algorithms/SegmentSegmentDistance3.h).
3. [Пересечение отрезка с плоскостью](./GeometryCore/Algorithms/SegmentPlaneIntersection3.h).
4. [Расстояние от точки до отрезка](./GeometryCore/Algorithms/PointSegmentDistance3.h).
5. [Расстояние от точки до точки](./GeometryCore/Algorithms/PointPointDistance3.h).

