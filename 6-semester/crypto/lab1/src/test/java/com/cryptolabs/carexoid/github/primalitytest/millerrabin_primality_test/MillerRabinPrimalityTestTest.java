package com.cryptolabs.carexoid.github.primalitytest.millerrabin_primality_test;

import org.junit.jupiter.api.Test;
import com.cryptolabs.carexoid.github.primalitytest.PrimesConstant;

import java.math.BigInteger;

import static org.junit.jupiter.api.Assertions.*;

class MillerRabinPrimalityTestTest {

    private static final int certainty = 100;

    @Test
    void isZeroPrimeShouldThrowArithmeticException() {
        assertThrows(ArithmeticException.class,
                () -> MillerRabinPrimalityTest.isProbablyPrime(BigInteger.ZERO, certainty),
                "BigInteger: modulus not positive");
    }

    @Test
    void isNegativePrimeShouldThrowArithmeticException() {
        assertThrows(ArithmeticException.class,
                () -> MillerRabinPrimalityTest.isProbablyPrime(BigInteger.valueOf(-1000), certainty),
                "BigInteger: modulus not positive");
    }

    @Test
    void isOnePrimeShouldReturnFalse() {
        assertFalse(MillerRabinPrimalityTest.isProbablyPrime(BigInteger.ONE, certainty));
    }

    @Test
    void isTwoPrimeShouldReturnTrue() {
        assertTrue(MillerRabinPrimalityTest.isProbablyPrime(BigInteger.TWO, certainty));
    }

    @Test
    void negativeCertaintyAlwaysReturnFalse() {
        assertFalse(MillerRabinPrimalityTest.isProbablyPrime(BigInteger.valueOf(13), -1));
        assertFalse(MillerRabinPrimalityTest.isProbablyPrime(BigInteger.valueOf(1000), -1));
    }

    @Test
    void zeroCertaintyAlwaysReturnFalse() {
        assertFalse(MillerRabinPrimalityTest.isProbablyPrime(BigInteger.valueOf(13), 0));
        assertFalse(MillerRabinPrimalityTest.isProbablyPrime(BigInteger.valueOf(1000), 0));
    }

    @Test
    void isProbablyPrimeShouldReturnTrue() {
        for (BigInteger prime : PrimesConstant.primes) {
            assertTrue(MillerRabinPrimalityTest.isProbablyPrime(prime, certainty));
        }
    }

    @Test
    void isProbablyPrimeShouldReturnFalse() {
        for (BigInteger notPrime : PrimesConstant.notPrimes) {
            assertFalse(MillerRabinPrimalityTest.isProbablyPrime(notPrime, certainty));
        }
    }

    @Test
    void isProbablyPrimeShouldReturnFalseForNotPrimesBiggerThanInt() {
        int numberOfIsPrimeFalseReturns = 0;
        for (BigInteger bigInteger : PrimesConstant.bigNotPrimes) {
            if (!MillerRabinPrimalityTest.isProbablyPrime(bigInteger, certainty)) {
                ++numberOfIsPrimeFalseReturns;
            }
        }

        assertEquals(99, numberOfIsPrimeFalseReturns, 1);
    }

    @Test
    void isProbablyPrimeShouldReturnTrueForPrimesBiggerThanInt() {
        int numberOfIsPrimeTrueReturns = 0;
        for (BigInteger bigInteger : PrimesConstant.bigPrimes) {
            if (MillerRabinPrimalityTest.isProbablyPrime(bigInteger, certainty)) {
                ++numberOfIsPrimeTrueReturns;
            }
        }

        assertEquals(99, numberOfIsPrimeTrueReturns, 1);
    }
}