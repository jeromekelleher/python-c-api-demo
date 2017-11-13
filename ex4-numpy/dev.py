"""
Example code for demostrating the demo Python C module.
"""

import numpy as np
import demo

print("Hello from demo")

n = 100000

# for _ in range(10000):
#     x = np.random.random(n)
#     y = np.random.random(n)
#     z = demo.fancy_algorithm(x, y)
#     assert np.all(z == (x * y))

for _ in range(10000):
    x = np.random.random(n)
    y = np.random.random(n - 1)
    try:
        z = demo.fancy_algorithm(x, y)
    except ValueError:
        pass
    else:
        assert False

