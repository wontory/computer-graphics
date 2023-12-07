import {
  forwardRef,
  useEffect,
  useImperativeHandle,
  useMemo,
  useRef,
} from 'react';
import { Vector3 } from 'three';
import { CuboidCollider, RigidBody, useRapier } from '@react-three/rapier';
import { RapierRaycastVehicle } from '../../lib/rapier-raycast-vehicle';
import ChassisBody from './ChassisBody';
import Wheel from './Wheel';

const Car = forwardRef(({ ...props }, ref) => {
  const rapier = useRapier();

  const vehicleRef = useRef(null);
  const chassisRigidBodyRef = useRef(null);

  const topLeftWheelObject = useRef(null);
  const topRightWheelObject = useRef(null);
  const bottomLeftWheelObject = useRef(null);
  const bottomRightWheelObject = useRef(null);

  const {
    indexRightAxis,
    indexForwardAxis,
    indexUpAxis,
    directionLocal: directionLocalArray,
    axleLocal: axleLocalArray,
    vehicleWidth,
    vehicleHeight,
    vehicleFront,
    vehicleBack,
    ...levaWheelOptions
  } = {
    radius: 0.45,

    indexRightAxis: 2,
    indexForwardAxis: 0,
    indexUpAxis: 1,

    directionLocal: [0, -1, 0],
    axleLocal: [0, 0, 1],

    suspensionStiffness: 30,
    suspensionRestLength: 0.3,
    maxSuspensionForce: 100000,
    maxSuspensionTravel: 0.3,

    sideFrictionStiffness: 1,
    frictionSlip: 1.4,
    dampingRelaxation: 2.3,
    dampingCompression: 4.4,

    rollInfluence: 0.01,

    customSlidingRotationalSpeed: -30,
    useCustomSlidingRotationalSpeed: true,

    forwardAcceleration: 1,
    sideAcceleration: 1,

    vehicleWidth: 1.4,
    vehicleHeight: -0.32,
    vehicleFront: -0.8,
    vehicleBack: 1.4,
  };

  const directionLocal = useMemo(
    () => new Vector3(...directionLocalArray),
    [directionLocalArray]
  );
  const axleLocal = useMemo(
    () => new Vector3(...axleLocalArray),
    [axleLocalArray]
  );

  const commonWheelOptions = {
    ...levaWheelOptions,
    directionLocal,
    axleLocal,
  };

  const wheels = [
    {
      object: topLeftWheelObject,
      options: {
        ...commonWheelOptions,
        chassisConnectionPointLocal: new Vector3(
          vehicleBack,
          vehicleHeight,
          vehicleWidth * 0.5
        ),
      },
    },
    {
      object: topRightWheelObject,
      options: {
        ...commonWheelOptions,
        chassisConnectionPointLocal: new Vector3(
          vehicleBack,
          vehicleHeight,
          vehicleWidth * -0.5
        ),
      },
    },
    {
      object: bottomLeftWheelObject,
      options: {
        ...commonWheelOptions,
        chassisConnectionPointLocal: new Vector3(
          vehicleFront,
          vehicleHeight,
          vehicleWidth * 0.5
        ),
      },
    },
    {
      object: bottomRightWheelObject,
      options: {
        ...commonWheelOptions,
        chassisConnectionPointLocal: new Vector3(
          vehicleFront,
          vehicleHeight,
          vehicleWidth * -0.5
        ),
      },
    },
  ];

  useImperativeHandle(ref, () => ({
    chassisRigidBody: chassisRigidBodyRef,
    rapierRaycastVehicle: vehicleRef,
    setBraking: () => {},
    wheels,
  }));

  useEffect(() => {
    vehicleRef.current = new RapierRaycastVehicle({
      world: rapier.world,
      chassisRigidBody: chassisRigidBodyRef.current,
      indexRightAxis,
      indexForwardAxis,
      indexUpAxis,
    });

    for (let i = 0; i < wheels.length; i++) {
      const options = wheels[i].options;
      vehicleRef.current.addWheel(options);
    }
  }, [
    chassisRigidBodyRef,
    vehicleRef,
    indexRightAxis,
    indexForwardAxis,
    indexUpAxis,
    directionLocal,
    axleLocal,
    levaWheelOptions,
    rapier.world,
    wheels,
  ]);

  return (
    <>
      <RigidBody
        {...props}
        colliders={false}
        position={[0, 5, 0]}
        ref={chassisRigidBodyRef}
        mass={150}
      >
        <CuboidCollider args={[2.0, 0.5, 1]} />
        <ChassisBody />
      </RigidBody>

      <group ref={topLeftWheelObject}>
        <Wheel
          rotation={[0, Math.PI / 2, 0]}
          side="left"
          radius={commonWheelOptions.radius}
        />
      </group>
      <group ref={topRightWheelObject}>
        <Wheel
          rotation={[0, Math.PI / 2, 0]}
          side="right"
          radius={commonWheelOptions.radius}
        />
      </group>
      <group ref={bottomLeftWheelObject}>
        <Wheel
          rotation={[0, Math.PI / 2, 0]}
          side="left"
          radius={commonWheelOptions.radius}
        />
      </group>
      <group ref={bottomRightWheelObject}>
        <Wheel
          rotation={[0, Math.PI / 2, 0]}
          side="right"
          radius={commonWheelOptions.radius}
        />
      </group>
    </>
  );
});

Car.displayName = 'Car';

export default Car;
