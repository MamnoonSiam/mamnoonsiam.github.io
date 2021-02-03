from manim import *

class HappyLine(Scene):
  def construct(self):
    a = [7, 6, 7, 5, 6, 4] # everything is taller than or equal to the stairs
    n = len(a)
    i_app = 3

    equiv = MathTex(r"\simeq")

    lbox = [[None for _ in range(100)] for _ in range(100)]
    rbox = [[None for _ in range(100)] for _ in range(100)]
    lvg = VGroup()
    rvg = VGroup()
    for i in range(n):
      for j in range(a[i]):
        lbox[i][j] = Rectangle(
          width=1,
          height=1,
          fill_opacity=0.2
        ).shift(RIGHT * i, UP * j)
        rbox[i][j] = lbox[i][j].copy()
        lvg += lbox[i][j]
        rvg += rbox[i][j]
    lvg.next_to(equiv, LEFT)
    rvg.next_to(equiv, RIGHT)
    self.add(lvg)
    self.add(rvg)

    ver_line = Line(
      start = rbox[0][n-1].get_center() + LEFT/2 + UP/2,
      end = rbox[0][0].get_center() + DOWN/2 + LEFT/2
    )
    hor_line = Line(
      start = rbox[0][0].get_center() + DOWN/2 + LEFT/2,
      end = rbox[n-1][0].get_center() + DOWN/2 + RIGHT/2
    )

    iboxes = VGroup(
      *[
        lbox[i_app][i] for i in range(a[i_app])
      ]
    )
    inxtboxes = VGroup(
      *[
        lbox[i_app+1][i] for i in range(a[i_app+1])
      ]
    )

    self.play(
      *[
        iboxes.animate.set_color(RED_B).set_fill(opacity=0.5),
        inxtboxes.animate.set_color(BLUE_B).set_fill(opacity=0.5),
      ]
    )

    self.play(
      lbox[i_app][a[i_app]-1].animate.move_to(
        lbox[i_app+1][a[i_app+1]-1].get_center() + UP
      )
    )
    self.play(
      lbox[i_app][a[i_app]-1].animate.set_color(
        BLUE_B
      )
    )

    self.wait(0.5)

    iboxes -= lbox[i_app][a[i_app]-1]
    inxtboxes += lbox[i_app][a[i_app]-1]

    self.play(
      *[
        iboxes.animate.shift(RIGHT),
        inxtboxes.animate.shift(LEFT)
      ]
    )

    self.wait(1)

    self.play(Write(equiv))

    self.wait(0.5)

    stair = VGroup()
    stair += ver_line
    stair += hor_line

    for i in range(n):
      j = n - i - 1
      center = rbox[i][j].get_center().copy();
      A = center + LEFT/2 + UP/2
      B = center + RIGHT/2 + UP/2
      C = center + RIGHT/2 + DOWN/2
      stair += Line(A, B)
      stair += Line(B, C)

    self.add(stair)

    stair_boxes = VGroup()
    non_stair_boxes = VGroup()

    for i in range(n):
      for j in range(a[i]):
        if j < n-i:
          stair_boxes += rbox[i][j]
        else:
          non_stair_boxes += rbox[i][j]

    blocks = [None for _ in range(n)]
    for i in range(n):
      if a[i] > n-i:
        blocks[i] = Rectangle(
          height = a[i] - (n-i),
          width = 1,
          fill_color = YELLOW_A,
          fill_opacity = 0.5,
          stroke_color = YELLOW_A
        ).move_to((rbox[i][a[i]-1].get_center() + rbox[i][n-i].get_center())/2)

    blocksVG = VGroup(
      *[
        blocks[i]
        for i in range(n) if blocks[i] != None
      ]
    )

    self.play(
      *[
        FadeIn(blocksVG),
        FadeOut(non_stair_boxes),
        FadeOut(stair_boxes)
      ]
    )
    self.wait(1)
    self.play(
      *[
        blocks[i_app].animate.set_color(RED_B),
        blocks[i_app+1].animate.set_color(BLUE_B)
      ]
    )
    self.wait(1)
    self.play(
      *[
        blocks[i_app].animate.move_to(
          rbox[i_app+1][n-(i_app+1)-1].get_center() + UP * (1/2 + blocks[i_app].get_height()/2),
        ),
        blocks[i_app+1].animate.move_to(
          rbox[i_app][n-i_app-1].get_center() + UP * (1/2 + blocks[i_app+1].get_height()/2),
        )
      ]
    )

    blocks[i_app], blocks[i_app+1] = blocks[i_app+1], blocks[i_app]


    self.wait(2)