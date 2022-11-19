# FFmpeg-OpenVINO-VAAPI
GPU inference & decode patches for ffmpeg DNN module. This project has been merged into cartwheel-ffmpeg of Intel. [Related PR](https://github.com/intel-media-ci/ffmpeg/pull/581) and [patch file](https://github.com/intel-media-ci/cartwheel-ffmpeg/pull/183).

## Environment
### System information
- Platform : ubuntu20.04
- CPU : Intel(R) Core(TM) i7-7700HQ CPU @ 2.80GHz
### Software dependency
- Intel Media Driver: [21.3.5](https://github.com/intel/media-driver/releases/tag/intel-media-21.3.5)
- GmmLib: [intel-gmmlib-21.3.1](https://github.com/intel/gmmlib/releases/tag/intel-gmmlib-21.3.1)
- Libva: [2.13.0](https://github.com/intel/libva/releases/tag/2.13.0)

## Install
```
git clone https://github.com/Kizna1ver/FFmpeg-OpenVINO-VAAPI.git
git submodule update --init --recursive 
apt install autoconf libtool libdrm-dev xorg xorg-dev openbox libx11-dev libgl1-mesa-glx libgl1-mesa-dev
```
### Gmmlib
```
cd gmmlib
mkdir build
cd build
cmake $SRC_DIR/gmmlib -DCMAKE_INSTALL_PREFIX=$ROOT_INSTALL_DIR
make -j8
make install
```
### Libva
```
cd libva
./autogen.sh --prefix=$ROOT_INSTALL_DIR
make -j8
make install
```
### Media driver
```
cd media-driver-intel-media-21.3.5
mkdir build
cd build
cmake $SRC_DIR/MediaSDK -DCMAKE_INSTALL_PREFIX=$ROOT_INSTALL_DIR
make -j8
make install
```
### OpenVINO
[Build OpenVINO™ Inference Engine](https://github.com/openvinotoolkit/openvino/wiki/BuildingCode#build-openvino-inference-engine)
```
# Install command for reference
cd openvino
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release -DENABLE_WHEEL=ON ..
make -j8
cmake --install ./ --prefix /opt/intel/openvino_2022
source /opt/intel/openvino_2022/setupvars.sh
```
### FFmpeg
You can apply this patches to your FFmpeg repo, or directly use FFmpeg in this repo. 
```
cd FFmpeg
apt install libx264-dev vainfo
sed -i 's/inference_engine_c_api/openvino_c/g' configure
./configure --extra-cflags=-I/opt/intel/openvino_2022/runtime/include/ie/ --extra-ldflags=-L/opt/intel/openvino_2022/runtime/lib/intel64/ --extra-ldflags=-L/opt/intel/openvino_2022/runtime/3rdparty/tbb/lib/ --enable-libopenvino --disable-lzma --enable-pic --enable-nonfree --disable-stripping --enable-hwaccel=h264_vaapi --enable-libfontconfig --enable-libfreetype --enable-gpl --enable-libx264 --enable-shared
make -j8
make install
```

## Run

### Detect & classify
```
cd resource
ffmpeg -hwaccel vaapi -vaapi_device /dev/dri/renderD128 -hwaccel_output_format vaapi -i cici672x384.mp4 -vf dnn_detect=dnn_backend=openvino:model=face-detection-adas-0001.xml:input=data:output=detection_out:confidence=0.6:labels=face-detection-adas-0001.label,hwdownload,format=nv12,dnn_classify=dnn_backend=openvino:model=emotions-recognition-retail-0003.xml:input=data:output=prob_emotion:confidence=0.3:labels=emotions-recognition-retail-0003.label:target=face,drawbox=box_source=side_data_detection_bboxes:t=5:color=red,drawtext=text_source=side_data_detection_bboxes:fontcolor=red:fontsize=30 -an -y faces.mp4
```
### processing
```
cd resource
ffmpeg -hwaccel vaapi -vaapi_device /dev/dri/renderD128 -hwaccel_output_format vaapi -i cici224.mp4 -vf dnn_processing=dnn_backend=openvino:model=fast-neural-style-mosaic-onnx.xml:input=input1:output=output1,format=rgb24 -y -c:v libx264 cici_gpu.mp4
```

## Addition
[FFmpeg VAAPI decode & ov2.0 inference demo](https://github.com/Kizna1ver/OpenVINO-RemoteBlob-Sample)
