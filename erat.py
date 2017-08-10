import unittest

class TestCases(unittest.TestCase):
    def test_3(self):
        self.assertEqual(primes(3), [2, 3])

    def test_10(self):
        self.assertEqual(primes(10), [2, 3, 5, 7])

    def test_30(self):
        self.assertEqual(primes(30), [2, 3, 5, 7, 11, 13, 17, 19, 23, 29])

def primes(n):
    '''Returns a list of prime numbers in the [2, n] interval.
    The algorithm is based on the Sieve of Eratostenes.'''

    # all numbers in the [2, n] interval are candidates
    candidates = list(range(2, n + 1))
    
    for i in range(len(candidates)):
        try:
            p = candidates[i]
        except IndexError:
            # oops, already exhausted the candidates list
            break

        j = 2

        while (p * j) <= n:
            try:
                candidates.remove(p * j)
            except ValueError:
                # candidate already removed
                pass
            finally:
                j += 1

    return candidates

if __name__ == '__main__':
    unittest.main()
