#include <stdio.h>

// Fuzzy set membership functions for temperature
double isHighTemperature(double temperature) {
    return (temperature >= 37.0) ? (temperature - 37.0) / 0.5 : 0.0;
}

double isMediumTemperature(double temperature) {
    if (temperature <= 36.0 || temperature >= 37.5) {
        return 0.0;
    } else if (temperature > 36.0 && temperature < 37.0) {
        return (temperature - 36.0) / 1.0;
    } else {
        return (37.5 - temperature) / 0.5;
    }
}

double isLowTemperature(double temperature) {
    return (temperature <= 36.0) ? (36.0 - temperature) / 1.0 : 0.0;
}

// Fuzzy set membership functions for cough
double isHighCough(double cough) {
    return (cough >= 3) ? (cough - 3) / 2.0 : 0.0;
}

double isMediumCough(double cough) {
    if (cough <= 1 || cough >= 4) {
        return 0.0;
    } else if (cough > 1 && cough < 3) {
        return (cough - 1) / 2.0;
    } else {
        return (4 - cough) / 1.0;
    }
}

double isLowCough(double cough) {
    return (cough <= 1) ? (1 - cough) / 1.0 : 0.0;
}

// Fuzzy logic inference
double fuzzyInference(double temperature, double cough, double *healthy, double *mildlySick, double *sick) {
    *healthy = (isMediumTemperature(temperature) * isLowCough(cough)) +
               (isMediumTemperature(temperature) * isLowCough(cough)) +
               (isLowTemperature(temperature) * isLowCough(cough));

    *mildlySick = (isHighTemperature(temperature) * isMediumCough(cough)) +
                  (isMediumTemperature(temperature) * isHighCough(cough)) +
                  (isLowTemperature(temperature) * isMediumCough(cough));

    *sick = (isHighTemperature(temperature) * isHighCough(cough)) +
            (isMediumTemperature(temperature) * isHighCough(cough)) +
            (isLowTemperature(temperature) * isHighCough(cough));

    // Defuzzification (centroid method)
    double denominator = (*healthy + *mildlySick + *sick);

    if (denominator == 0.0) {
        // Avoid division by zero
        return 0.0;
    }

    return ((isMediumTemperature(temperature) * isLowCough(cough) * 35.0 +
             *mildlySick * 36.5 +
             *sick * 37.5) / denominator);
}

int main() {
    double temperature, cough, healthy, mildlySick, sick;

    // Input temperature and cough level
    printf("Enter the temperature in Celsius: ");
    scanf("%lf", &temperature);

    printf("Enter the cough level (0-5): ");
    scanf("%lf", &cough);

    // Fuzzy logic inference
    double result = fuzzyInference(temperature, cough, &healthy, &mildlySick, &sick);

    // Output the result
    printf("\nDecision: %.2lf\n", result);

    // Determine health condition
    if (result <= 36.5) {
        printf("The person is Healthy.\n");
    } else if (result > 36.5 && result <= 37.0) {
        printf("The person is Mildly Sick.\n");
    } else {
        printf("The person is Sick.\n");
    }

    return 0;
}
