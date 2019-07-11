from Point import Point


def main() :
    p1 = Point(0.,1.)
    p2 = Point(2.,3.)

    p3 = p1 + p2
    p4 = p1 - p2

    print(p1)
    print(p2)
    print(p3)
    print(p4)

    points = []
    f = open("points.txt")
    for line in f.readlines():
        p = Point()
        p.input(line)
        points.append(p)

    for point in points:
        print(point)




if __name__ == "__main__" :
    main()
