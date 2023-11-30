import { Suspense } from 'react';
import { Canvas } from '@react-three/fiber';
import { Physics } from '@react-three/cannon';
import Heightfield from './components/HeightField';
import { generateHeightmap } from './components/HeightField';
import Car from './components/Car';

function App({ scale = 40 }) {
  return (
    <Suspense fallback={<div>Loading...</div>}>
      <Canvas>
        <Physics>
          <ambientLight intensity={0.5} />
          <directionalLight position={[0, 3, 0]} castShadow />
          <pointLight position={[0, 13, 0]} intensity={10} power={1024} />
          <Heightfield
            elementSize={(scale * 1) / 128}
            heights={generateHeightmap({
              height: 128,
              number: 10,
              scale: 5,
              width: 128,
            })}
            position={[-scale / 2, 0, scale / 2]}
            rotation={[-Math.PI / 2, 0, 0]}
          />
          <Car />
        </Physics>
      </Canvas>
    </Suspense>
  );
}

export default App;
