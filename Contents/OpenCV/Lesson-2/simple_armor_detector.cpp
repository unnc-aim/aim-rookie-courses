#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>
#include <opencv2/opencv.hpp>



struct Light {
    cv::RotatedRect box;
    cv::Point2f center{};
    float angle{0.0f};
    float length{0.0f};
    float width{0.0f};
    bool valid{false};
    bool isRed{false};
};

cv::Mat preprocess(const cv::Mat & image);
std::vector<Light> findLightsStrip(const cv::Mat & raw_img, const cv::Mat & bin_img);

static double rotatedRectIntersectionArea(const cv::RotatedRect &r1, const cv::RotatedRect &r2) {
    std::vector<cv::Point2f> interPts;
    int ret = cv::rotatedRectangleIntersection(r1, r2, interPts);
    std::vector<cv::Point> poly;
    poly.reserve(interPts.size());
    for (auto &p : interPts) poly.emplace_back(cv::Point(cv::saturate_cast<int>(p.x), cv::saturate_cast<int>(p.y)));
    return std::abs(cv::contourArea(poly));
}

static void filterOverlappingLights(std::vector<Light> &lights, double overlap_thresh = 0.5, double center_dup_thresh = 10.0) {
    if (lights.size() < 2) return;
    std::vector<bool> remove(lights.size(), false);
    for (size_t i = 0; i < lights.size(); ++i) {
        if (remove[i]) continue;
        double area_i = lights[i].length * lights[i].width;
        for (size_t j = i + 1; j < lights.size(); ++j) {
            if (remove[j]) continue;
            double area_j = lights[j].length * lights[j].width;
            
            double inter = rotatedRectIntersectionArea(lights[i].box, lights[j].box);
            double min_area = std::min(area_i, area_j);
            if (min_area > 0 && inter / min_area > overlap_thresh) {
                
                if (area_i >= area_j) remove[j] = true; else remove[i] = true;
                continue;
            }
            
            double dx = lights[i].center.x - lights[j].center.x;
            double dy = lights[i].center.y - lights[j].center.y;
            double dist = std::sqrt(dx*dx + dy*dy);
            
            double avg_len = (lights[i].length + lights[j].length) * 0.5;
            double adaptive_thresh = std::max(center_dup_thresh, avg_len * 0.15);
            if (dist < adaptive_thresh) {
                
                if (area_i >= area_j) remove[j] = true; else remove[i] = true;
            }
        }
    }
    
    std::vector<Light> filtered;
    filtered.reserve(lights.size());
    for (size_t k = 0; k < lights.size(); ++k) if (!remove[k]) filtered.push_back(lights[k]);
    lights.swap(filtered);
}


std::vector<std::pair<Light, Light>> matchLights(const std::vector<Light> &lights,
                                                 float size_ratio_tol = 0.1f,
                                                 float angle_tol_deg = 10.0f,
                                                 float dist_ratio_target = 3.0f,
                                                 float dist_ratio_tol = 1.5f);

int main() {
    cv::Mat bgr_image = cv::imread("armor.png");

    cv::imshow("origin", bgr_image);
    const cv::Mat bin = preprocess(bgr_image);

    std::vector<Light> lights = findLightsStrip(bgr_image, bin);

    
    filterOverlappingLights(lights, 0.5, 12.0);

    cv::Mat result = bgr_image.clone();
    for (const auto &L : lights) {

        cv::Scalar color = L.isRed ? cv::Scalar(0,0,255) : cv::Scalar(255,0,0);

        cv::Point2f verts[4];
        L.box.points(verts);
        for (int k = 0; k < 4; ++k) cv::line(result, verts[k], verts[(k+1)%4], color, 2);
        cv::circle(result, L.center, 3, cv::Scalar(0,255,0), cv::FILLED);
        std::string info = "len:" + std::to_string((int)L.length) + " w:" + std::to_string((int)L.width) + "angle:" + std::to_string((int)L.angle);
        cv::putText(result, info, L.center + cv::Point2f(5,-5), cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar(255,255,255), 1);
    }


    const auto pairs = matchLights(lights);
    for (const auto & p : pairs) {
        const Light &L1 = p.first;
        const Light &L2 = p.second;
        const cv::String color = L1.isRed ? "RED" : "BLUE";

        cv::line(result, L1.center, L2.center, cv::Scalar(0,255,0), 2);

        cv::Point2f mid = (L1.center + L2.center) * 0.5f;
        cv::putText(result, "ARMOR: " + color, mid + cv::Point2f(-20, -10), cv::FONT_HERSHEY_SIMPLEX, 2, L1.isRed ? cv::Scalar(0,0,255) : cv::Scalar(255,0,0), 2);
    }

    cv::imshow("result", result);
    cv::waitKey(0);
    return 0;
}

cv::Mat preprocess(const cv::Mat & image) {
    cv::Mat gray_img;

    cv::cvtColor(image, gray_img, cv::COLOR_BGR2GRAY);

    cv::Mat binary_img;
    cv::threshold(gray_img, binary_img, 128, 255, cv::THRESH_BINARY);

    return binary_img;

}


std::vector<Light> findLightsStrip(const cv::Mat & raw_img, const cv::Mat & bin_img) {
    using std::vector;
    int minimal_height = 80;
    int minimal_width = 10;
    vector<vector<cv::Point> > contours;
    vector<cv::Vec4i> hierarchy;
    cv::findContours(bin_img, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    std::vector<Light> lights;
    for (const auto & contour : contours) {

        cv::RotatedRect rrect = cv::minAreaRect(contour);
        cv::Size2f sz = rrect.size;
        float length = std::max(sz.width, sz.height);
        float width = std::min(sz.width, sz.height);


        if (width <= 0 || length / width < 2.0f || width < minimal_width || length < minimal_height) {
            continue;
        }


        cv::Point2f center = rrect.center;
        float angle = rrect.angle;

        cv::Rect bbox = rrect.boundingRect();
        bbox &= cv::Rect(0,0,raw_img.cols, raw_img.rows);
        if (bbox.width == 0 || bbox.height == 0) continue;

        int sum_r = 0;
        int sum_b = 0;
        const cv::Mat roi = raw_img(bbox);
        
        for (int i = 0; i < roi.rows; ++i) {
            for (int j = 0; j < roi.cols; ++j) {
                cv::Point2f pt((float)(j + bbox.x), (float)(i + bbox.y));
                if (cv::pointPolygonTest(contour, pt, false) >= 0) {
                    auto pix = roi.at<cv::Vec3b>(i, j);
                    sum_r += pix[2];
                    sum_b += pix[0];
                }
            }
        }

        bool isRed = (sum_r > sum_b);

        
        Light L;
        L.box = rrect;
        L.center = center;
        L.angle = angle;
        L.length = length;
        L.width = width;
        L.valid = true;
        L.isRed = isRed;

        lights.push_back(L);
    }

    return lights;
}

std::vector<std::pair<Light, Light>> matchLights(const std::vector<Light> &lights,
                                                 float size_ratio_tol,
                                                 float angle_tol_deg,
                                                 float dist_ratio_target,
                                                 float dist_ratio_tol) {
    std::vector<std::pair<Light, Light>> preferred;
    if (lights.size() < 2) return preferred;

    for (size_t i = 0; i < lights.size(); ++i) {
        for (size_t j = i + 1; j < lights.size(); ++j) {
            const Light &L1 = lights[i];
            const Light &L2 = lights[j];

            
            float min_len = std::min(L1.length, L2.length);
            float max_len = std::max(L1.length, L2.length);
            if (max_len <= 0) continue;
            float size_ratio = min_len / max_len;
             if (size_ratio < (1.0f - size_ratio_tol)) continue;

            auto longVec = [](const cv::RotatedRect &r) {
                cv::Point2f pts[4];
                r.points(pts);
                float bestLen2 = 0.0f;
                cv::Point2f bestVec(1.0f, 0.0f);
                for (int i = 0; i < 4; ++i) {
                    cv::Point2f a = pts[i];
                    cv::Point2f b = pts[(i+1)%4];
                    cv::Point2f v = b - a;
                    float len2 = v.x*v.x + v.y*v.y;
                    if (len2 > bestLen2) {
                        bestLen2 = len2;
                        float norm = std::sqrt(len2);
                        if (norm > 0) bestVec = cv::Point2f(v.x / norm, v.y / norm);
                    }
                }
                return bestVec;
            };
            cv::Point2f v1 = longVec(L1.box);
            cv::Point2f v2 = longVec(L2.box);

            float dot = v1.x * v2.x + v1.y * v2.y;
            dot = std::clamp(dot, -1.0f, 1.0f);
            float angle_deg = std::acos(std::abs(dot)) * 180.0f / CV_PI; 
             if (angle_deg > angle_tol_deg) continue;

            cv::Point2f c = L2.center - L1.center;
            cv::Point2f base = cv::Point2f(v1.x + v2.x, v1.y + v2.y);
            float base_norm = std::sqrt(base.x*base.x + base.y*base.y);
            if (base_norm < 1e-3f) {
                base = v1;
                base_norm = std::sqrt(base.x*base.x + base.y*base.y);
            }
            base.x /= base_norm; base.y /= base_norm;
            cv::Point2f perp(-base.y, base.x);

            float lateral_dist = std::abs(c.x * perp.x + c.y * perp.y);
            float avg_len = (L1.length + L2.length) * 0.5f;
            if (avg_len <= 0) continue;
            float dist_ratio = lateral_dist / avg_len;
             if (std::abs(dist_ratio - dist_ratio_target) > dist_ratio_tol) continue;

            float longitudinal = std::abs(c.x * base.x + c.y * base.y);
             if (longitudinal / avg_len > 0.6f) continue;

            if (L1.isRed == L2.isRed) {
                preferred.emplace_back(L1, L2);
            }
        }
    }

    std::vector<std::pair<Light, Light>> result;
    for (const auto &p : preferred) result.push_back(p);
    return result;
}
