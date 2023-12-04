import { Sphere } from '@react-three/drei';
import { BallCollider, RigidBody } from '@react-three/rapier';

function Ball() {
  return (
    <RigidBody position={[0, 5, 0]} colliders={false} gravityScale={4}>
      <BallCollider args={[1]} position={[0, 1, 0]} />
      <Sphere position-y={1}>
        <meshStandardMaterial color={'hotpink'} />
      </Sphere>
    </RigidBody>
  );
}

export default Ball;
