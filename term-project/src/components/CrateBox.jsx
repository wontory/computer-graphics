import { Box } from '@react-three/drei';
import { RigidBody } from '@react-three/rapier';

function CrateBox() {
  return (
    <RigidBody position={[3, 3, 3]} gravityScale={4}>
      <Box>
        <meshStandardMaterial color="royalblue" />
      </Box>
    </RigidBody>
  );
}

export default CrateBox;
