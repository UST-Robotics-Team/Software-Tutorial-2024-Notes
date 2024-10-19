# Mecanum Wheel

> We did NOT provide Mecanum Wheels in RDC 2024. However, you might try to propose it as extra types of material and ask for approval in the FAQ.

<details>

<summary>Authors</summary>

Dicaprio Cheung

(Reference from HKUST Robocon Advance Tutorial 2023)

</details>

## Table of Content

[#prerequisite](mecanum-wheel.md#prerequisite "mention")

[#what-is-a-mecanum-wheel](mecanum-wheel.md#what-is-a-mecanum-wheel "mention")

[#how-does-it-work](mecanum-wheel.md#how-does-it-work "mention")

[#things-to-work-on](mecanum-wheel.md#things-to-work-on "mention")

## Prerequisite

You are recommended to read the [Omniwheel](omniwheel.md) notes before continuing this notes

## What is a Mecanum wheel?

<figure><img src="../images/image (4) (1) (1).png" alt="" width="375"><figcaption></figcaption></figure>



Mecanum wheel is sometimes called the Swedish wheel or Ilon wheel. It is also an omnidirectional wheel design for a land-based vehicle to move in any direction. To understand how it works, here is an [interactive page](https://seamonsters-2605.github.io/archive/mecanum/).

## How does it work?

<figure><img src="../images/image (9).png" alt="" width="338"><figcaption><p>Left: a 4 wheel omniwheel wheelbase. Right: a Mecanum wheelbase</p></figcaption></figure>

The small discs (called rollers) of a Mecanum wheel are 45 degrees to the turning direction. So, a vertically installed Mecanum wheel is equivalent to a 45-degree installed omniwheel. Therefore, the math for the two wheelbases above is the same.

<figure><img src="../images/image (11).png" alt="" width="223"><figcaption><p>Blue: Wheel Drive Direction, Black: Movement Direction</p></figcaption></figure>

Although the wheel looks like it is moving in the blue arrows' direction, it is actually applying forces in the black arrows' direction.&#x20;

So, we can define the Forces A, B, C, and D in these directions like this. Then follow the steps in [this omniwheel notes](omniwheel.md#simplest-case-wheelbase-moving-forward) to calculate how much forces we need to move the wheelbase forward.

<figure><img src="../images/image (12).png" alt="" width="226"><figcaption></figcaption></figure>

{% hint style="info" %}
Remember to check if your mech teammates installed the Mecanum wheels correctly like the picture below. Or else your wheelbase can't move and rotate correctly

&#x20;![](../images/image (8).png)
{% endhint %}

## Things to work on

Your team should have chosen a wheelbase for your RDC robot. Find out the general equation for your chosen wheelbase (i.e. speeds of all wheels in relation to Fx, Fy, and Torque) and write a control function (C code) to control your wheelbase.&#x20;

Given Fx = x, Fy = y, Torque = θ,

A = ? B = ? C = ? D = ?
