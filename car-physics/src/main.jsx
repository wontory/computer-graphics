import ReactDOM from 'react-dom/client';
import { Canvas } from '@react-three/fiber';
import Scene from './Scene.jsx';
import './index.css';

ReactDOM.createRoot(document.getElementById('root')).render(
  <Canvas>
    <Scene />
  </Canvas>
);
