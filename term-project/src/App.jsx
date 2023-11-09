import { Suspense } from 'react';
import { Canvas } from '@react-three/fiber';
import { Physics } from '@react-three/cannon';
import Camera from './components/Camera';
import Heightfield from './components/HeightField';
import { generateHeightmap } from './components/HeightField';

function App({ scale = 10 }) {
  return (
    <Suspense fallback={<div>Loading...</div>}>
      <Canvas>
        <Camera />
        <Physics>
          <ambientLight intensity={0.5} />
          <directionalLight position={[0, 3, 0]} castShadow />
          <Heightfield
            elementSize={(scale * 1) / 128}
            heights={generateHeightmap({
              height: 128,
              number: 10,
              scale: 1,
              width: 128,
            })}
            position={[-scale / 2, 0, scale / 2]}
            rotation={[-Math.PI / 2, 0, 0]}
          />
        </Physics>
      </Canvas>
    </Suspense>
  );
}

export default App;
