package com.cryptolabs.carexoid.github.karatsuba;

import org.junit.jupiter.api.Test;

import java.math.BigInteger;
import java.util.Random;

import static org.junit.jupiter.api.Assertions.assertEquals;

class KaratsubaAlgorithmTest {

    @Test
    void multiplicationOnZeroShouldReturnZero() {
        assertEquals(BigInteger.ZERO,
                KaratsubaAlgorithm.multiply(new BigInteger("2034954578765486095"), BigInteger.ZERO));
    }

    @Test
    void negativeNumberShouldReturnNegativeWithMultiplyingOnPositive() {
        assertEquals(new BigInteger("-500000000000000"),
                KaratsubaAlgorithm.multiply(new BigInteger("-5"), new BigInteger("100000000000000")));
    }

    @Test
    void negativeNumberShouldReturnPositiveWithMultiplyingOnNegative() {
        assertEquals(new BigInteger("500000000000000"),
                KaratsubaAlgorithm.multiply(new BigInteger("-5"), new BigInteger("-100000000000000")));
    }

    @Test
    void resultsForMultiplicationShouldBeSameAsLibMultiplication() {
        BigInteger a, b;
        Random rand = new Random();

        for (int i = 0; i < 100; i++) {
            a = BigInteger.valueOf(Math.abs(rand.nextLong()));
            b = BigInteger.valueOf(Math.abs(rand.nextLong()));

            assertEquals(a.multiply(b), KaratsubaAlgorithm.multiply(a, b));
        }
    }
}