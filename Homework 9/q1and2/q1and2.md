# Exercise 1
## Question
Let a camera have position $(8,4,- 3)$ in world coordinates. Describe this position in spherical coordinates as a radius $r$ from the world’s origin, and two angles $\theta$ and $\phi$, where $\theta$ is measured from the positive $x$ axis toward the positive $z$ axis, and $\phi$ is measured from the positive $y$ axis toward the $x-z$ plane.

## Answer
$$
r = \sqrt{x^2 + y^2 + z^2} = \sqrt{8^2 + 4^2 + (-3)^2} = \sqrt{89} \approx 9.433981132
$$

$$
\theta = \tan ^{-1}(\frac{z}{x}) = \tan ^{-1}(\frac{-3}{8}) \approx \tan ^{-1}(-0.375) \approx -0.3587706703 \text{ radians}
$$

$$
\phi = \cos ^{-1}(\frac{y}{r}) = \cos ^{-1}(\frac{4}{\sqrt{89}}) = \cos ^{-1}(\frac{4}{9.43}) \approx \cos ^{-1}(0.4241781548) \approx 1.13274217
$$

# Exercise 2
## Question
Consider a spotlight, as shown in the above diagram. Therein, $L$ is the direction of the light source from the point $P$. Spot direction refers to the direction the spotlight is pointing, while cutoff angle refers to the **half-angle** of the cone of light produced by the spotlight. Let a spotlight have position $(5,10,2)$, be pointed at $(3,2,1)$, and have a cutoff angle of 30°. For a point in space $P = (x_p,y_p,z_p)$ determine a function $f (x,y,z)$ such that $f (x_p,y_p,z_p) > 0$ if $P$ is inside the spotlight’s cone of light, and $f (x_p,y_p,z_p) < 0$ if $P$ is outside the spotlight’s cone of light.

## Answer
Let $A = (5,10,2)$ and $B = (3,2,1)$.

Then the direction of the spotlight $\vec{D}$ is the vector $\vec{D} = B - A = (3-5, 2-10, 1-2) = (-1,-8,-1)$.

$P$ is some point such that $P = (x,y,z)$.

$\vec{L} = P - A = (x-5, y-10, z-2)$

$\text{cuttoff angle } = \cos(\theta _{c}) = \cos(30^\circ) = \cos(\frac{\pi}{6}) = \frac{\sqrt{3}}{2} \approx 0.8660254038$
